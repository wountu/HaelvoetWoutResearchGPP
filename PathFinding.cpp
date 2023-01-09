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

