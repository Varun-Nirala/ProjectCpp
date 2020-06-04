#pragma once
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <list>
#include <map>

template<typename T>
class Node
{
	public:
		using value_type			= T;
		using pair_type			= typename std::pair<Node<T> * /* Node which can be reached */, int /* Weight associated with it */>;
		using vec_type			= typename std::vector<pair_type>;
		using iter_type			= typename vec_type::iterator;
		using const_iter_type	= typename vec_type::const_iterator;

	public:
		explicit Node(const T &data)
			: mData(data)
		{}

		~Node()
		{
			for (auto pp : mToNode)
			{
				delete pp.first;
			}
			mToNode.clear();
		}

		bool addEdge(Node<T> *dst, int weight = 0)
		{
			iter_type it = search(dst);

			if (it != mToNode.end())
			{
				// if already present just update the weight
				it->second = weight;
			}
			else
			{
				mToNode.push_back(make_pair(dst, weight));
			}
			return true;
		}

		bool isConnected(const Node<T>& dst) const
		{
			return !(search(dst) == mToNode.end());
		}

		int getWeight(const Node<T>& dst) const
		{
			return search(dst)->second;
		}

		bool isConnected(const T& dst) const
		{
			return !(search(dst) == mToNode.end());
		}

		int getWeight(const T& dst) const
		{
			return search(dst)->second;
		}

		const T& getData() const
		{
			return mData;
		}

		bool removeEdge(const T &dst)
		{
			iter_type it = search(dst);

			if (it != mToNode.end())
			{
				mToNode.erase(it);
				return true;
			}
			return false;
		}

		vec_type& getAllNode()
		{
			return mToNode;
		}

	private:
		iter_type search(const Node<T> *dst)
		{
			return std::find_if(mToNode.begin(), mToNode.end(), 
				[&](pair_type &pp) -> bool
			{
				return pp.first == dst;
			});
		}

		iter_type search(const T &dst)
		{
			return std::find_if(mToNode.begin(), mToNode.end(),
				[&](pair_type  &nPair) -> bool
			{
				return nPair.first->mData == dst;
			});
		}

		const_iter_type search(const Node<T> *dst) const
		{
			return std::find_if(mToNode.begin(), mToNode.end(),
				[&](const pair_type &pp) -> bool
			{
				return pp.first == dst;
			});
		}

		const_iter_type search(const T &dst) const
		{
			return std::find_if(mToNode.begin(), mToNode.end(),
				[&](const pair_type  &nPair) -> bool
			{
				return nPair.first->mData == dst;
			});
		}

	private:
		vec_type		mToNode;
		T			mData;
};

template <typename T>
class Graph
{
	public:
		using value_type				= T;
		using vec_type				= typename std::vector<Node<T> *>;
		using iter_type				= typename vec_type::iterator;

	public:
		// It should always succeed, it will either create new edge or update the existing with new weight
		bool addEdge(const T &src, const T &dst, int weight = 0)
		{
			Node<T> *srcNode, *dstNode;

			// Search or create srcNode
			iter_type it = search(src);
			if (it == mAllNodes.end())
			{
				srcNode = addNode(src);
			}
			else
			{
				srcNode = *it;
			}

			// Search or create dstNode
			it = search(dst);
			if (it == mAllNodes.end())
			{
				dstNode = addNode(dst);
			}
			else
			{
				dstNode = *it;
			}

			// Now we are sure that both node exists
			return srcNode->addEdge(dstNode, weight);
		}

		// Provide weight to delete only that path
		bool removeEdge(const T &src, const T &dst)
		{
			iter_type it = search(src);
			if (it != mAllNodes.end())
			{
				return (*it)->removeEdge(dst);
			}
			return false;
		}

		// return true if dst is directly connected to src 
		bool isConnected(const T &src, const T &dst)
		{
			iter_type it = search(src);
			if (it != mAllNodes.end())
			{
				return (*it)->isConnected(dst);
			}
			return false;
		}

		// return true if dst is directly connected to src, and fills up the weight ref,
		// otherwise just return false
		bool getWeight(const T&src, const T &dst, int &weight)
		{
			iter_type it = search(src);
			if (it != mAllNodes.end())
			{
				weight = (*it)->getWeight(dst);
				return true;
			}
			return false;
		}

		bool hasNode(const T &val) const
		{
			return !(search(val) == mAllNodes.end());
		}

		Node<T>* getNode(const T &val)
		{
			return (*search(val));
		}

		// Traversal Algorithms
		void BFS(const T &src)
		{
			if (mAllNodes.empty())
				return;

			std::map<T, bool> mVisited;
			for (auto p : mAllNodes)
			{
				mVisited[p->getData()] = false;
			}

			mVisited[src] = true;

			std::list<Node<T>*> nodeQeue;
			nodeQeue.push_back(getNode(src));

			Node<T> *currNode = NULL;
			while (!nodeQeue.empty())
			{
				currNode = nodeQeue.front();
				nodeQeue.pop_front();

				std::cout << currNode->getData() << " ";

				for (const std::pair<Node<T> *, int> nodePair : currNode->getAllNode())
				{
					std::map<T, bool>::iterator it = mVisited.find(nodePair.first->getData());

					if (it != mVisited.end())
					{
						if (!it->second)
						{
							it->second = true;
							nodeQeue.push_back(nodePair.first);
						}
					}
				}
			}
			cout << endl;
		}

		void DFS(const T &src)
		{
			if (mAllNodes.empty())
				return;

			std::map<T, bool> mVisited;
			for (auto p : mAllNodes)
			{
				mVisited[p->getData()] = false;
			}

			std::list<Node<T>*> nodeQeue;
			nodeQeue.push_front(getNode(src));

			Node<T> *currNode = NULL;
			while (!nodeQeue.empty())
			{
				currNode = nodeQeue.front();
				nodeQeue.pop_front();

				if (!mVisited[currNode->getData()])
				{
					std::cout << currNode->getData() << " ";
					mVisited[currNode->getData()] = true;
					for (const std::pair<Node<T> *, int> nodePair : currNode->getAllNode())
					{
						nodeQeue.push_front(nodePair.first);
					}
				}
			}
			cout << endl;
		}

	private:
		iter_type search(const T &val)
		{
			return std::find_if(mAllNodes.begin(), mAllNodes.end(), [&](Node<T> *data) {
				return data->getData() == val;
			});
		}

	private:
		Node<T> *addNode(const T &data)
		{
			Node<T> *node = new Node<T>(data);
			mAllNodes.push_back(node);
			return node;
		}

	private:
		vec_type		mAllNodes;
};