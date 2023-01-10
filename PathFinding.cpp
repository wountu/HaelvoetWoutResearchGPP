#include "PathFinding.h"
#include <algorithm>

Node helper::GetNodeOnPoint(Utils::Vector2 point, std::vector<Node> nodes)
{
	for (const Node& node : nodes)
	{
		Utils::Rect rect(node.leftTop, node.width, node.height);
		if (Functions::IsPointInRect(point, rect))
			return node;
	}
	return Node{};
};

std::vector<Utils::Vector2> pathfinding::CalculatePath(Utils::Vector2 startPos, Utils::Vector2 point, std::vector<Node> nodes) //AStar
{
	helper help{};
	std::vector<Utils::Vector2> path{};
	std::vector<NodeRecord> openList{};
	std::vector<NodeRecord> closedList{};
	NodeRecord currentRecord;

	Node startNode{ help.GetNodeOnPoint(startPos, nodes) };
	Node endNode{ help.GetNodeOnPoint(point, nodes) };
	openList.push_back(NodeRecord(startNode, Connection{}, 0.f, GetHeuristicCost(startPos, point)));

	while (!openList.empty())
	{
		currentRecord = *std::min_element(openList.begin(), openList.end());
		Node currentNode{ currentRecord.node };

		if (currentNode == endNode)
		{
			break;
		}

		std::vector<Node>nodeNeigbours = currentNode.neighbours;
		for (Node node : nodeNeigbours)
		{
			float costSoFar{ currentRecord.costSoFar + node.cost };
			float totalCost{ costSoFar + GetHeuristicCost(node.centrePoint, point) };
			NodeRecord listNode{ node, Connection{}, costSoFar, totalCost };
			auto find{ std::find_if(closedList.begin(), closedList.end(), [&](NodeRecord record) {return record.node == node; }) };

			if (find != closedList.end())
			{
				if (find->costSoFar < listNode.costSoFar)
					continue;
				
			}
			else
			{
				find = std::find_if(openList.begin(), openList.end(), [&](NodeRecord record) {return record.node == node; });

				if (find != openList.end())
				{
					if (find->costSoFar < listNode.costSoFar)
						continue;
					else openList.erase(find);
				}
			}
			openList.push_back(listNode);
		}

		openList.erase(std::remove(openList.begin(), openList.end(), currentRecord));
		closedList.push_back(currentRecord);
	}

	if (currentRecord.node == endNode)
	{
		while (currentRecord.node != startNode)
		{
			path.push_back(currentRecord.node.centrePoint);

			std::vector<Node> neighbours{ currentRecord.node.neighbours };
			for (Node node : neighbours)
			{
				auto find{ std::find_if(closedList.begin(), closedList.end(), [&](NodeRecord record) {return record.node == node; }) };

				if (find != closedList.end())
				{
					currentRecord = *find;
				}
			}
		}

		path.push_back(startPos);
	}

	std::reverse(path.begin(), path.end());
	return path;
}

float pathfinding::GetHeuristicCost(Utils::Vector2 start, Utils::Vector2 end)
{
	Utils::Vector2 toDestination{ end - start };
	return std::max(abs(toDestination.x), abs(toDestination.y));
}

