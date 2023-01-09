#pragma once
#include "Utils.h"
#include "SDLUtil.h"
#include <vector>

struct Node;

struct helper
{
	Node GetNodeOnPoint(Utils::Vector2 point, std::vector<Node> nodes);
};

struct Node
{
	Utils::Vector2 leftTop{};
	const float width{};
	const float height{};
	int idx{};
	
	Utils::Vector2 centrePoint{};
	std::vector<Node> neighbours{};

	Node() = default;
	Node(Utils::Vector2 _leftTop, float _width, float _height, int index) : leftTop(_leftTop), width(_width), height(_height), idx(index)
	{
		centrePoint.x = leftTop.x + width / 2.f; 
		centrePoint.y = leftTop.y + height / 2.f;
	}

	void Render(SDLUtil* pSdl) const
	{
		Utils::Rect rect{ leftTop, width, height };
		pSdl->DrawRect(rect);
		pSdl->DrawCircle(centrePoint, 2.f);
	}

	void SetIndex(int index)
	{
		idx = index;
	}

	std::vector<Node> GetNeighbours(std::vector<Node> nodes, float maxWidth, float maxHeight)
	{
		helper help{};
		Utils::Rect screen{ Utils::Vector2{0,0}, maxWidth, maxHeight };

		Utils::Vector2 leftTopNeighbour{};
		leftTopNeighbour.x = centrePoint.x - width;
		leftTopNeighbour.y = centrePoint.y - height;
		if (Functions::IsPointInRect(leftTopNeighbour, screen))
		{
			Node topLeft{ help.GetNodeOnPoint(leftTopNeighbour, nodes) };
			neighbours.push_back(topLeft);
		}

		Utils::Vector2 topNeigbour{};
		topNeigbour.x = centrePoint.x;
		topNeigbour.y = centrePoint.y - height;
		if (Functions::IsPointInRect(topNeigbour, screen))
		{
			Node top{ help.GetNodeOnPoint(topNeigbour, nodes) };
			neighbours.push_back(top);
		}

		Utils::Vector2 topRightNeigbour{};
		topRightNeigbour.x = centrePoint.x + width;
		topRightNeigbour.y = centrePoint.y + height;
		if (Functions::IsPointInRect(topRightNeigbour, screen))
		{
			Node topRight{ help.GetNodeOnPoint(topRightNeigbour, nodes) };
			neighbours.push_back(topRight);
		}
		
		Utils::Vector2 leftNeigbour{};
		leftNeigbour.x = centrePoint.x - width;
		leftNeigbour.y = centrePoint.y;
		if (Functions::IsPointInRect(leftNeigbour, screen))
		{
			Node left{ help.GetNodeOnPoint(leftNeigbour, nodes) };
			neighbours.push_back(left);
		}

		return neighbours;
	}
};

struct Connection {
	Node from{};
	Node to{};

	Connection() = default;
	Connection(Node _from, Node _to) : from(_from), to(_to) {};

	void Render(SDLUtil* pSdl) const
	{
		pSdl->DrawLine(from.centrePoint, to.centrePoint);
	}
};


struct Graph
{
	Utils::Vector2 nodeDimension{};
	const float totalWidth{};
	const float totalHeight{};

	int rows{};
	int cols{};
	int nrOfNodes;
	std::vector<Node> nodes{};
	std::vector<Connection> connections{};

	Graph() = default;
	Graph(Utils::Vector2 _nodeDimension, float width, float height)
		:nodeDimension(_nodeDimension), totalWidth(width), totalHeight(height)
	{
		rows = totalWidth / nodeDimension.x;
		cols = totalHeight / nodeDimension.y;
		nrOfNodes = int(rows * cols);

		for (size_t idx{}; idx < nrOfNodes; ++idx)
		{
			Utils::Vector2 leftTop{ (idx % rows) * nodeDimension.x, (idx / rows) * nodeDimension.y };

			nodes.push_back(Node(leftTop, nodeDimension.x, nodeDimension.y, idx));
		}

		for (Node node : nodes)
		{
			node.GetNeighbours(nodes, width, height);

			for (const Node& neigbourNode : node.neighbours)
			{
				connections.push_back(Connection( node, neigbourNode ));
			}
		}
	};

	void Render(SDLUtil* pSdl) const
	{
		pSdl->ChangeColor(0, 0, 0, 127.f);
		for (const Node& node : nodes)
		{
			node.Render(pSdl);
		}

		pSdl->ChangeColor(255, 255, 255, 127.f);
		for (const Connection& connection : connections)
		{
			connection.Render(pSdl);
		}
	}
};


namespace pathfinding
{
	std::vector<Utils::Vector2> CalculatePath(Utils::Vector2 point, std::vector<Node> nodes);
}

