package two

func NewMapAccumulator(in chan Node) chan map[string]Node {
	newMap := make(map[string]Node)

	return NewAccumulator(in, generateMap, newMap)
}

func generateMap(node Node, accum map[string]Node) map[string]Node {
	accum[node.name] = node
	return accum
}
