package one

import "regexp"

type NodeParser struct {
	nodePattern regexp.Regexp
}

func NewNodeParser(in chan string) chan Node {
	np := NodeParser{
		nodePattern: *regexp.MustCompile(`^(...) = \((...), (...)\)$`),
	}
	return NewPipelineStep(in, np.parseNode)
}

func (np *NodeParser) parseNode(in string) Node {
	matches := np.nodePattern.FindStringSubmatch(in)

	return Node{
		name: matches[1],
		branches: [2]string{
			matches[2],
			matches[3],
		},
	}
}
