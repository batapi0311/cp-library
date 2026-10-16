template <class Type>
class WeightedUnionFind
{
public:

	WeightedUnionFind() = default;

	/// @brief 重み付き Union-Find 木を構築します。
	/// @param n 要素数
	explicit WeightedUnionFind(size_t n)
		: m_parents(n)
		, m_sizes(n, 1)
		, m_diffWeights(n)
	{
		std::iota(m_parents.begin(), m_parents.end(), 0);
	}

	/// @brief 頂点 i の root のインデックスを返します。
	/// @param i 調べる頂点のインデックス
	/// @return 頂点 i の root のインデックス
	int find(int i)
	{
		if (m_parents[i] == i)
		{
			return i;
		}

		const int root = find(m_parents[i]);

		m_diffWeights[i] += m_diffWeights[m_parents[i]];

		// 経路圧縮
		return (m_parents[i] = root);
	}

	/// @brief a のグループと b のグループを統合します。
	/// @param a 一方のインデックス
	/// @param b 他方のインデックス
	/// @param w (b の重み) - (a の重み)
	void merge(int a, int b, Type w)
	{
		w += weight(a);
		w -= weight(b);

		a = find(a);
		b = find(b);

		if (a != b)
		{
			// union by size (小さいほうが子になる）
			if (m_sizes[a] < m_sizes[b])
			{
				std::swap(a, b);
				w = -w;
			}

			m_sizes[a] += m_sizes[b];
			m_parents[b] = a;
			m_diffWeights[b] = w;
		}
	}

	/// @brief (b の重み) - (a の重み) を返します。
	/// @param a 一方のインデックス
	/// @param b 他方のインデックス
	/// @remark a と b が同じグループに属さない場合の結果は不定です。
	/// @return (b の重み) - (a の重み)
	Type diff(int a, int b)
	{
		return (weight(b) - weight(a));
	}

	/// @brief a と b が同じグループに属すかを返します。
	/// @param a 一方のインデックス
	/// @param b 他方のインデックス
	/// @return a と b が同じグループに属す場合 true, それ以外の場合は false
	bool connected(int a, int b)
	{
		return (find(a) == find(b));
	}

	/// @brief i が属するグループの要素数を返します。
	/// @param i インデックス
	/// @return i が属するグループの要素数
	int size(int i)
	{
		return m_sizes[find(i)];
	}

private:

	// m_parents[i] は i の 親,
	// root の場合は自身が親
	std::vector<int> m_parents;

	// グループの要素数 (root 用)
	// i が root のときのみ, m_sizes[i] はそのグループに属する要素数を表す
	std::vector<int> m_sizes;

	// 重み
	std::vector<Type> m_diffWeights;

	Type weight(int i)
	{
		find(i); // 経路圧縮
		return m_diffWeights[i];
	}
};
