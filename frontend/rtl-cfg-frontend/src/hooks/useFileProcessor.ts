import { useState, useCallback } from "react";
import axios from "axios";

interface FileProcessorState {
  fileContent: string | null;
  fileName: string | null;
  isLoading: boolean;
  error: string | null;
  processedCode: string | null; // CFG code
  graphData: string | null; // SVG string
  handleFileUpload: (file: File) => void;
  clearFile: () => void;
}

export const useFileProcessor = (): FileProcessorState => {
  const [fileContent, setFileContent] = useState<string | null>(null);
  const [fileName, setFileName] = useState<string | null>(null);
  const [isLoading, setIsLoading] = useState<boolean>(false);
  const [error, setError] = useState<string | null>(null);
  const [processedCode, setProcessedCode] = useState<string | null>(null); // CFG code
  const [graphData, setGraphData] = useState<string | null>(null); // SVG string

  const handleFileUpload = useCallback(async (file: File) => {
    setError(null);

    if (!file.name.endsWith(".v")) {
      setError("Invalid file type. Please upload a Verilog (.v) file.");
      return;
    }

    setIsLoading(true);

    const formData = new FormData();
    formData.append("rtl_file", file);
    setFileName(file.name);

    try {
      // Save file content for FileViewer (optional, not used for processedCode)
      const text = await file.text();
      setFileContent(text);

      // Send to backend and get CFG and DOT code
      const response = await axios.post(
        `${import.meta.env.VITE_API_URL}/api/convert/`,
        formData
      );
      const cfg = response.data.cfg;
      const dot = response.data.dot;
      setProcessedCode(cfg);

      // Dynamically import Graphviz and render SVG from DOT
      const { Graphviz } = await import("@hpcc-js/wasm-graphviz");
      const graphviz = await Graphviz.load();
      const svg = graphviz.dot(dot);
      setGraphData(svg);

      setIsLoading(false);
    } catch (err) {
      setError("Failed to process file or render graph.");
      setIsLoading(false);
      setProcessedCode(null);
      setGraphData(null);
    }
  }, []);

  const clearFile = useCallback(() => {
    setFileContent(null);
    setFileName(null);
    setProcessedCode(null);
    setGraphData(null);
    setError(null);
  }, []);

  return {
    fileContent,
    fileName,
    isLoading,
    error,
    processedCode,
    graphData,
    handleFileUpload,
    clearFile,
  };
};
