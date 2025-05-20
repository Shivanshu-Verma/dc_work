import React, { useCallback, useRef } from "react";
import { useTheme } from "../context/ThemeContext";
import { Download, Loader2 } from "lucide-react";

interface GraphViewerProps {
  data: string | null; // SVG string
  isLoading: boolean;
}

const GraphViewer: React.FC<GraphViewerProps> = ({ data, isLoading }) => {
  const { theme } = useTheme();
  const graphRef = useRef<HTMLDivElement>(null);

  const handleDownload = useCallback(() => {
    if (graphRef.current && data) {
      const svg = data;
      const blob = new Blob([svg], { type: "image/svg+xml" });
      const url = URL.createObjectURL(blob);
      const a = document.createElement("a");
      a.href = url;
      a.download = `graph.svg`;
      a.click();
      URL.revokeObjectURL(url);
    }
  }, [data]);

  const containerClasses = `
    rounded-xl 
    border
    h-[600px]
    relative
    transition-colors 
    duration-200
    ${
      theme === "dark"
        ? "bg-slate-800 border-slate-700"
        : "bg-white border-slate-200"
    }
  `;

  return (
    <div className="h-full">
      <div className="flex items-center justify-between mb-4">
        <h2 className="text-xl font-semibold">Graph Visualization</h2>
      </div>

      <div className={containerClasses + " flex flex-col"}>
        {isLoading ? (
          <div className="flex flex-col items-center justify-center h-full text-center p-6">
            <Loader2 className="h-12 w-12 text-blue-500 animate-spin mb-4" />
            <p className="text-lg font-medium">Generating graph...</p>
          </div>
        ) : data ? (
          <>
            <div
              ref={graphRef}
              className="flex-1 min-h-0 w-full overflow-auto flex items-start justify-center relative max-h-full"
              style={{ maxHeight: "100%" }}
              dangerouslySetInnerHTML={{ __html: data }}
            />
            <button
              onClick={handleDownload}
              className="absolute bottom-4 right-4 flex items-center gap-2 px-4 py-2 rounded-lg bg-blue-600 text-white hover:bg-blue-700 transition-colors shadow-lg"
            >
              <Download className="h-4 w-4" />
              Download SVG
            </button>
          </>
        ) : (
          <div className="flex flex-col items-center justify-center h-full text-center p-6">
            <p className="text-lg font-medium mb-2">No graph to display</p>
            <p className="text-sm text-slate-500 dark:text-slate-400">
              Upload a Verilog (.v) file to see the visualization
            </p>
          </div>
        )}
      </div>
    </div>
  );
};

export default GraphViewer;
