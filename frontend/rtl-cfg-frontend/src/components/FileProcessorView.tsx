import React from "react";
import FileUploader from "./FileUploader";
import CodeViewer from "./CodeViewer";
import GraphViewer from "./GraphViewer";
import { useFileProcessor } from "../hooks/useFileProcessor";

const FileProcessorView: React.FC = () => {
  const {
    fileContent,
    fileName,
    isLoading,
    error,
    handleFileUpload,
    clearFile,
    processedCode,
    graphData,
  } = useFileProcessor();

  return (
    <div className="max-w-[1600px] mx-auto px-2 sm:px-4">
      <div className="flex flex-col gap-6 md:grid md:grid-cols-12 md:gap-6">
        {/* Upload box */}
        <div className="md:col-span-3 order-1">
          <FileUploader
            onFileUpload={handleFileUpload}
            isLoading={isLoading}
            error={error}
            hasFile={!!fileContent}
            onClear={clearFile}
            acceptedTypes=".v"
          />
          {/* Code display below upload on mobile, right on desktop */}
          <div className="mt-6 md:mt-6">
            <CodeViewer
              code={processedCode} // CFG code
              fileName={fileName}
              isLoading={isLoading}
            />
          </div>
        </div>
        {/* Graph visual below code on mobile, right on desktop */}
        <div className="md:col-span-9 order-2 mt-6 md:mt-0">
          <GraphViewer
            data={graphData} // SVG string
            isLoading={isLoading}
          />
        </div>
      </div>
    </div>
  );
};

export default FileProcessorView;
