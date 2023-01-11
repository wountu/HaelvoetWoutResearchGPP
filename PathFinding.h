#pragma once
#include "Utils.h"
#include "SDLUtil.h"
#include <vector>

struct Node;

struct helper
{
	Node GetNodeOnPoint(Utils::Vector2 point, std::vector<Node> nodes, float width, float height, int rows, int cols);
};

struct Node
{
	Utils::Vector2 leftTop{};
	float width{};
	float height{};
	int idx{};
	int cost{ 20 };
	bool visited{};
	
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

	std::vector<Node> GetNeighbours(std::vector<Node> nodes, float maxWidth, float maxHeight, int rows, int cols)
	{
		helper help{};
		Utils::Rect screen{ Utils::Vector2{0,0}, maxWidth, maxHeight };

		Utils::Vector2 leftTopNeighbour{};
		leftTopNeighbour.x = centrePoint.x - width;
		leftTopNeighbour.y = centrePoint.y - height;
		if (Functions::IsPointInRect(leftTopNeighbour, screen))
		{
			Node topLeft{ help.GetNodeOnPoint(leftTopNeighbour, nodes, maxWidth, maxHeight, rows, cols) };
			neighbours.push_back(topLeft);
		}

		Utils::Vector2 topNeigbour{};
		topNeigbour.x = centrePoint.x;
		topNeigbour.y = centrePoint.y - height;
		if (Functions::IsPointInRect(topNeigbour, screen))
		{
			Node top{ help.GetNodeOnPoint(topNeigbour, nodes, maxWidth, maxHeight, rows, cols) };
			neighbours.push_back(top);
		}

		Utils::Vector2 topRightNeigbour{};
		topRightNeigbour.x = centrePoint.x + width;
		topRightNeigbour.y = centrePoint.y - height;
		if (Functions::IsPointInRect(topRightNeigbour, screen))
		{
			Node topRight{ help.GetNodeOnPoint(topRightNeigbour, nodes, maxWidth, maxHeight, rows, cols) };
			neighbours.push_back(topRight);
		}
		
		Utils::Vector2 leftNeigbour{};
		leftNeigbour.x = centrePoint.x - width;
		leftNeigbour.y = centrePoint.y;
		if (Functions::IsPointInRect(leftNeigbour, screen))
		{
			Node left{ help.GetNodeOnPoint(leftNeigbour, nodes, maxWidth, maxHeight, rows, cols) };
			neighbours.push_back(left);
		}

		Utils::Vector2 rightNeighbour{};
		rightNeighbour.x = centrePoint.x + width;
		rightNeighbour.y = centrePoint.y;
		if (Functions::IsPointInRect(rightNeighbour, screen))
		{
			Node right{ help.GetNodeOnPoint(rightNeighbour, nodes, maxWidth, maxHeight, rows, cols) };
			neighbours.push_back(right);
		}

		Utils::Vector2 botLeft{};
		botLeft.x = centrePoint.x - width;
		botLeft.y = centrePoint.y + height;
		if (Functions::IsPointInRect(botLeft, screen))
		{
			Node botLeftNode{ help.GetNodeOnPoint(botLeft, nodes, maxWidth, maxHeight, rows, cols) };
			neighbours.push_back(botLeftNode);
		}

		Utils::Vector2 bot{};
		bot.x = centrePoint.x;
		bot.y = centrePoint.y + height;
		if (Functions::IsPointInRect(bot, screen))
		{
			Node botNode{ help.GetNodeOnPoint(bot, nodes, maxWidth, maxHeight, rows, cols) };
			neighbours.push_back(botNode);
		}

		Utils::Vector2 botRight{};
		botRight.x = centrePoint.x + width;
		botRight.y = centrePoint.y + height;
		if (Functions::IsPointInRect(botRight, screen))
		{
			Node botRightNode{ help.GetNodeOnPoint(botRight, nodes, maxWidth, maxHeight, rows, cols) };
			neighbours.push_back(botRightNode);
		}

		return neighbours;
	}

	void operator=(const Node& other)
	{
		leftTop = other.leftTop;
		width = other.width;
		height = other.height;
		idx = other.idx;
		cost = other.cost;
		centrePoint = other.centrePoint;
		neighbours = other.neighbours;
	}

	bool operator==(const Node& other) const
	{
		return leftTop == other.leftTop
			&& width == other.width
			&& height == other.height
			&& idx == other.idx
			&& cost == other.cost
			&& centrePoint == other.centrePoint
			&& neighbours == other.neighbours;
	}

	bool operator!=(const Node& other) const
	{
		return leftTop != other.leftTop
			|| width != other.width
			|| height != other.height
			|| idx != other.idx
			|| cost != other.cost
			|| centrePoint != other.centrePoint
			|| neighbours != other.neighbours;
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

	void operator=(const Connection& other) 
	{
		from = other.from;
		to = other.to;
	}

	bool operator==(const Connection& other) const
	{
		return from == other.from
			&& to == other.to;
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

		for (size_t idx{}; idx < nodes.size(); ++idx)
		{
	
			nodes[idx].GetNeighbours(nodes, width, height, rows, cols);

			//for (const Node& neigbourNode : nodes[idx].neighbours)
			//{
			//	connections.push_back(Connection(nodes[idx], neigbourNode));
			//}
			//std::cout << nodes[0].neighbours.size() << "\n";
			//std::cout << idx << "\n";
		}

		/*for (Node node : nodes)
		{
			node.GetNeighbours(nodes, width, height);

			for (const Node& neigbourNode : node.neighbours)
			{
				connections.push_back(Connection(node, neigbourNode));
			}
		}*/
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

struct NodeRecord {
	Node node{};
	Connection connection{};
	float costSoFar{ 0.f };
	float estimatedTotalCost{0.f};

	NodeRecord() = default;
	NodeRecord(Node _node, Connection _connection, float cost, float heuristic)
		: node{ _node }, connection{ _connection }, costSoFar{ cost }, estimatedTotalCost{ heuristic }{};

	void operator=(const NodeRecord& other)
	{
		node = other.node;
		connection = other.connection;
		costSoFar = other.costSoFar;
		estimatedTotalCost = other.estimatedTotalCost;
	};

	bool operator<(const NodeRecord& other) const
	{
		return estimatedTotalCost < other.estimatedTotalCost;
	};

	bool operator==(const NodeRecord& other) const
	{
		return node == other.node
			&& connection == other.connection
			&& costSoFar == other.costSoFar
			&& estimatedTotalCost == other.estimatedTotalCost;
	}
};

namespace pathfinding
{
	std::vector<Utils::Vector2> CalculatePath(Utils::Vector2 startPos, Utils::Vector2 point, std::vector<Node> nodes);
	float GetHeuristicCost(Utils::Vector2 start, Utils::Vector2 end);
}

