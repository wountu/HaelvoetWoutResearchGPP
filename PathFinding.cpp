#include "PathFinding.h"
#include "Utils.h"
#include <algorithm>

Node helper::GetNodeOnPoint(Utils::Vector2 point, std::vector<Node> nodes, float width, float height, int rows, int cols, Utils::Vector2 nodeDimensions)
{
	const float nodeW{ 40 }, nodeH{ 40 };

	if (width == 0 || height == 0 || cols == 0 || rows == 0)
	{

		for (const Node& node : nodes)
		{
			Utils::Rect rect(node.leftTop, node.width, node.height);
			if (Functions::IsPointInRect(point, rect))
				return node;
		}

	}
	else
	{
		int col{ static_cast<int>(point.x / nodeW) };
		int row{ static_cast<int>(point.y / nodeH) };
		int idx{ col * rows + row };

		for (const Node& node : nodes)
		{
			if (node.idx == idx)
				return node;
		}
	}

	return Node{};
};

std::vector<Utils::Vector2> pathfinding::CalculatePath(Utils::Vector2 startPos, Utils::Vector2 point, std::vector<Node> nodes, Graph graph) //AStar
{
	helper help{};
	std::vector<Utils::Vector2> path{};
	std::vector<NodeRecord> openList{};
	std::vector<NodeRecord> closedList{};
	NodeRecord currentRecord;

	Node startNode{ help.GetNodeOnPoint(startPos, nodes, 0.f, 0.f, 0, 0, Utils::Vector2{ nodes[0].width, nodes[0].height}) };
	Node endNode{ help.GetNodeOnPoint(point, nodes, 0.f, 0.f, 0, 0, Utils::Vector2{ nodes[0].width, nodes[0].height}) };
	openList.push_back(NodeRecord(startNode, Connection{}, 0.f, GetHeuristicCost(startPos, point)));

	while (!openList.empty())
	{
		//std::cout << openList.size() << "\n";
		currentRecord = *std::min_element(openList.begin(), openList.end());
		Node currentNode{ currentRecord.node };

		if (currentNode == endNode)
		{
			closedList.push_back(currentRecord);
			break;
		}

		std::vector<Node*>nodeNeigbours = currentNode.GetNeighbours(nodes, graph.totalWidth, graph.totalHeight, graph.rows, graph.cols);
		for (Node* node : nodeNeigbours)
		{
			float costSoFar{ currentRecord.costSoFar + node->cost };
			float totalCost{ costSoFar + GetHeuristicCost(node->centrePoint, point) };
			NodeRecord listNode{ *node, Connection{}, costSoFar, totalCost };
			//auto find{ std::find_if(closedList.begin(), closedList.end(), [&](NodeRecord record) {return record.node == node; }) };

			bool find{};
			NodeRecord closedListNode{};
			for (const NodeRecord& record : closedList)
			{
				if (record.node == *node)
				{
					find = true;
					closedListNode = record;
					break;
				}
			}

			if (find)
			{
				if (closedListNode.costSoFar < listNode.costSoFar)
					continue;
				
			}

			else
			{
				find = false;
				NodeRecord openListRecord{};
				for (const NodeRecord& record : openList)
				{
					if (record.node == *node)
					{
						find = true;
						openListRecord = record;
						break;
					}
				}

				//find = std::find_if(openList.begin(), openList.end(), [&](NodeRecord record) {return record.node == node; });

				if (find)
				{
					if (openListRecord.costSoFar < listNode.costSoFar)
						continue;

					else
					{
						openList.erase(std::remove(openList.begin(), openList.end(), openListRecord), openList.end());
						//for (size_t idx{}; idx < openList.size(); ++idx)
						//{
						//	if (openList[idx] == openListRecord)
						//	{
						//		openList[idx] = openList[openList.size() - 1];
						//	}
						//}

						//openList.erase(openListRecord);
					}

				}
			}
			openList.push_back(listNode);
		}

		//openList.erase(openList.begin(), openList.end());
		openList.erase(std::remove(openList.begin(), openList.end(), currentRecord));
		closedList.push_back(currentRecord);
	}

	if (currentRecord.node == endNode)
	{
		auto result = std::find(closedList.begin(), closedList.end(), currentRecord);
		if (result != closedList.end())
		{
			result->node.visited = true;
		}
		
		while (currentRecord.node != startNode)
		{
			path.push_back(currentRecord.node.centrePoint);

	//bool allNodesVisited{};
	//Node endNode{ help.GetNodeOnPoint(point, nodes, 0.f, 0.f, 0, 0) };
	//Node currentNode{ help.GetNodeOnPoint(startPos, nodes, 0.f, 0.f, 0, 0) };

				if (find != closedList.end())
				{

					//if(!closedList.empty())
					//	closedList.erase(std::remove(closedList.begin(), closedList.end(), currentRecord), closedList.end());



	std::reverse(path.begin(), path.end());
	return path;
}

float pathfinding::GetHeuristicCost(Utils::Vector2 start, Utils::Vector2 end)
{
	return abs(start.x - end.x) + abs(start.y - end.y);
}

