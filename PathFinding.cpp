#include "PathFinding.h"
#include <algorithm>

Node helper::GetNodeOnPoint(Utils::Vector2 point, std::vector<Node> nodes, float width, float height, int rows, int cols)
{
	for (const Node& node : nodes)
	{
		Utils::Rect rect(node.leftTop, node.width, node.height);

		if (width == 0 || height == 0 || cols == 0 || rows == 0)
		{
			if (Functions::IsPointInRect(point, rect))
				return node;
		}

		else
		{
			int row{ int(point.x / width) };
			int col{ int(point.y / height) };

			int idx{ col * rows + row };
			if (node.idx == idx)
				return node;
		}
	}
	return Node{};
};

std::vector<Utils::Vector2> pathfinding::CalculatePath(Utils::Vector2 startPos, Utils::Vector2 point, std::vector<Node> nodes) //AStar
{
	//helper help{};
	//std::vector<Utils::Vector2> path{};
	//std::vector<NodeRecord> openList{};
	//std::vector<NodeRecord> closedList{};
	//NodeRecord currentRecord;

	//Node startNode{ help.GetNodeOnPoint(startPos, nodes, 0.f, 0.f, 0, 0) };
	//Node endNode{ help.GetNodeOnPoint(point, nodes, 0.f, 0.f, 0, 0) };
	//openList.push_back(NodeRecord(startNode, Connection{}, 0.f, GetHeuristicCost(startPos, point)));

	//while (!openList.empty())
	//{
	//	currentRecord = *std::min_element(openList.begin(), openList.end());
	//	Node currentNode{ currentRecord.node };

	//	if (currentNode == endNode)
	//	{
	//		break;
	//	}

	//	std::vector<Node>nodeNeigbours = currentNode.neighbours;
	//	for (Node node : nodeNeigbours)
	//	{
	//		float costSoFar{ currentRecord.costSoFar + node.cost };
	//		float totalCost{ costSoFar + GetHeuristicCost(node.centrePoint, point) };
	//		NodeRecord listNode{ node, Connection{}, costSoFar, totalCost };
	//		//auto find{ std::find_if(closedList.begin(), closedList.end(), [&](NodeRecord record) {return record.node == node; }) };

	//		bool find{};
	//		NodeRecord closedListNode{};
	//		for (const NodeRecord& record : closedList)
	//		{
	//			if (record.node == node)
	//			{
	//				find = true;
	//				closedListNode = record;
	//				break;
	//			}
	//		}

	//		if (!find)
	//		{
	//			if (closedListNode.costSoFar < listNode.costSoFar)
	//				continue;
	//			
	//		}
	//		else
	//		{
	//			find = false;
	//			NodeRecord openListRecord{};
	//			for (const NodeRecord& record : openList)
	//			{
	//				if (record.node == node)
	//				{
	//					find = true;
	//					openListRecord = record;
	//					break;
	//				}
	//			}

	//			//find = std::find_if(openList.begin(), openList.end(), [&](NodeRecord record) {return record.node == node; });

	//			if (!find)
	//			{
	//				if (openListRecord.costSoFar < listNode.costSoFar)
	//					continue;
	//				else
	//				{
	//					for (size_t idx{}; idx < openList.size(); ++idx)
	//					{
	//						if (openList[idx] == openListRecord)
	//						{
	//							openList[idx] = openList[openList.size() - 1];
	//						}
	//					}

	//					//openList.erase(openListRecord);
	//				}

	//			}
	//		}
	//		openList.push_back(listNode);
	//	}

	//	openList.erase(std::remove(openList.begin(), openList.end(), currentRecord));
	//	closedList.push_back(currentRecord);
	//}

	//if (currentRecord.node == endNode)
	//{
	//	while (currentRecord.node != startNode)
	//	{
	//		path.push_back(currentRecord.node.centrePoint);

	//		std::vector<Node> neighbours{ currentRecord.node.neighbours };
	//		for (Node node : neighbours)
	//		{
	//			auto find{ std::find_if(closedList.begin(), closedList.end(), [&](NodeRecord record) {return record.node == node; }) };

	//			if (find != closedList.end())
	//			{
	//				currentRecord = *find;
	//			}
	//		}
	//	}

	//	path.push_back(startPos);
	//}

	//std::reverse(path.begin(), path.end());
	//return path;

	//bool allNodesVisited{};
	//Node endNode{ help.GetNodeOnPoint(point, nodes, 0.f, 0.f, 0, 0) };
	//Node currentNode{ help.GetNodeOnPoint(startPos, nodes, 0.f, 0.f, 0, 0) };

	//while (!allNodesVisited)
	//{
	//	int lowestCost{ FLT_MAX };
	//	Node nextNode{};
	//	for (Node neigbour : currentNode.neighbours)
	//	{
	//		if (neigbour.cost < lowestCost)
	//		{
	//			lowestCost = neigbour.cost;
	//			currentNode = neigbour;
	//		}

	//	}
	//	currentNode.visited = true;
	//}


	helper help{};
	std::vector<Utils::Vector2> path{};
	std::vector<NodeRecord> closedList{};
	std::vector<NodeRecord> openList{};

	Node startNode{ help.GetNodeOnPoint(startPos, nodes, 0.f, 0.f, 0, 0) };
	Node endNode{ help.GetNodeOnPoint(point, nodes, 0.f, 0.f, 0, 0) };
	std::cout << "Node at idx is startnode: " << startNode.idx << "\n";
	std::cout << "Node at idx is endNode: " << endNode.idx << "\n";

	NodeRecord currentRecord{};
	currentRecord.node = startNode;

	openList.emplace_back(currentRecord);

	while (!openList.empty())
	{
		currentRecord = *std::min_element(openList.begin(), openList.end());

		if (currentRecord.node.idx == endNode.idx)
		{
			break;
		}

		auto neighbours = currentRecord.node.neighbours;
		std::vector<float> totalCosts{};

		for (const auto& neigbour : neighbours)
		{
			float costSoFar = currentRecord.costSoFar + neigbour->cost;
			float heuristic = GetHeuristicCost(neigbour->centrePoint, endNode.centrePoint);
			float totalCost = costSoFar + heuristic;

			totalCosts.push_back(totalCost);

			//auto result = std::find(closedList.begin(), closedList.end(), neigbour);
			//if (result != closedList.end())
			//{
			//	//Remove neigbour if cheaper
			//}

			//result = std::find(openList.begin(), openList.end(), neigbour);
			//if (result != openList.end())
			//{
			//	//Remove neighbour if cheaper
			//}

			//NodeRecord newRecord{}
		}
	}

	//closedList.push_back()

	 return std::vector<Utils::Vector2>{};
}

float pathfinding::GetHeuristicCost(Utils::Vector2 start, Utils::Vector2 end)
{
	return abs(start.x - end.x) + abs(start.y - end.y);
}

