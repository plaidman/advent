package one

func NewProductionStepParser(in chan []string) chan ProductionStep {
	return NewPipelineStep(in, parseProductionStep)
}

func parseProductionStep(almanacGroup []string) ProductionStep {
	lineChan := make(chan string)
	mappingChan := NewMappingParser(lineChan)
	sliceChan := NewSliceAccumulator(mappingChan)

	for _, almanacLine := range almanacGroup {
		lineChan <- almanacLine
	}
	close(lineChan)

	return NewProductionStep(<-sliceChan)
}
