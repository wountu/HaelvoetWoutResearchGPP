#include "PathFinding.h"

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

std::vector<Utils::Vector2> pathfinding::CalculatePath(Utils::Vector2 point, std::vector<Node> nodes)
{
	helper help{};
	Node node{ help.GetNodeOnPoint(point, nodes) };

	std::vector<Utils::Vector2> path{};
	path.push_back(node.centrePoint);

	return path;
}
