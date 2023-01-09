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

		//ADD functionality to get connections at a certain node(with idx's)
		//ADD finish the rest of connections(right, botleft, bot, botright)
	}

	path.push_back(endNode.centrePoint);

	return path;
}

float pathfinding::GetHeuristicCost(Utils::Vector2 start, Utils::Vector2 end)
{
	Utils::Vector2 toDestination{ end - start };
	return std::max(abs(toDestination.x), abs(toDestination.y));
}

