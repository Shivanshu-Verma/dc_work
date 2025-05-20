import React, { useCallback, useState } from "react";
import { Upload, X, Loader2 } from "lucide-react";
import { useTheme } from "../context/ThemeContext";

interface FileUploaderProps {
  onFileUpload: (file: File) => void;
  onClear: () => void;
  isLoading: boolean;
  error: string | null;
  hasFile: boolean;
  acceptedTypes: string;
}

const FileUploader: React.FC<FileUploaderProps> = ({
  onFileUpload,
  onClear,
  isLoading,
  error,
  hasFile,
  acceptedTypes,
}) => {
  const { theme } = useTheme();
  const [isDragging, setIsDragging] = useState(false);
  const [uploadProgress, setUploadProgress] = useState(0);

  React.useEffect(() => {
    if (isLoading) {
      setUploadProgress(0);
      const interval = setInterval(() => {
        setUploadProgress((prev) => {
          const next = prev + Math.random() * 20;
          return next > 95 ? 95 : next;
        });
      }, 100);

      return () => {
        clearInterval(interval);
        setUploadProgress(100);
      };
    }
  }, [isLoading]);

  const handleDragOver = useCallback((e: React.DragEvent<HTMLDivElement>) => {
    e.preventDefault();
    setIsDragging(true);
  }, []);

  const handleDragLeave = useCallback((e: React.DragEvent<HTMLDivElement>) => {
    e.preventDefault();
    setIsDragging(false);
  }, []);

  const handleDrop = useCallback(
    (e: React.DragEvent<HTMLDivElement>) => {
      e.preventDefault();
      setIsDragging(false);

      if (e.dataTransfer.files && e.dataTransfer.files.length > 0) {
        const file = e.dataTransfer.files[0];
        onFileUpload(file);
      }
    },
    [onFileUpload]
  );

  const handleFileChange = useCallback(
    (e: React.ChangeEvent<HTMLInputElement>) => {
      if (e.target.files && e.target.files.length > 0) {
        const file = e.target.files[0];
        onFileUpload(file);
        e.target.value = ""; // Reset input value
      }
    },
    [onFileUpload]
  );

  const containerClasses = `
    rounded-xl 
    border-2 
    border-dashed 
    transition-all 
    duration-200
    h-48
    flex 
    flex-col 
    items-center 
    justify-center
    p-4
    ${isDragging ? "border-blue-500 bg-blue-50 dark:bg-slate-800" : ""} 
    ${error ? "border-red-400" : "border-amber-300"}
    ${
      theme === "dark"
        ? "bg-slate-800 hover:bg-slate-700"
        : "bg-amber-50 hover:bg-amber-100"
    }
  `;

  return (
    <div>
      <div className="flex items-center justify-between mb-4">
        <h2 className="text-xl font-semibold">Upload RTL File</h2>
        {hasFile && !isLoading && (
          <button
            onClick={onClear}
            className="text-sm flex items-center gap-1 px-3 py-1 rounded bg-red-100 text-red-600 hover:bg-red-200 dark:bg-red-900/30 dark:text-red-300 dark:hover:bg-red-800/30 transition-colors"
          >
            <X className="h-3 w-3" /> Clear
          </button>
        )}
      </div>

      <div
        className={containerClasses}
        onDragOver={handleDragOver}
        onDragLeave={handleDragLeave}
        onDrop={handleDrop}
      >
        {isLoading ? (
          <div className="flex flex-col items-center justify-center text-center">
            <Loader2 className="h-8 w-8 text-blue-500 animate-spin mb-2" />
            <p className="text-sm font-medium mb-2">Uploading your file...</p>
            <div className="w-full max-w-[200px] bg-slate-200 dark:bg-slate-700 rounded-full h-1.5 mb-1">
              <div
                className="bg-blue-500 h-1.5 rounded-full transition-all duration-300 ease-out"
                style={{ width: `${uploadProgress}%` }}
              />
            </div>
            <p className="text-xs text-slate-500 dark:text-slate-400">
              {Math.round(uploadProgress)}% complete
            </p>
          </div>
        ) : (
          <>
            <Upload
              className={`h-8 w-8 mb-2 ${
                error ? "text-red-500" : "text-blue-500"
              }`}
            />

            <p className="text-sm font-medium mb-1 text-center">
              {error ? "Upload Error" : "Click or drag RTL file"}
            </p>

            {error ? (
              <p className="text-red-500 text-xs text-center max-w-xs">
                {error}
              </p>
            ) : (
              <p className="text-xs text-slate-500 dark:text-slate-400 text-center">
                Supports .v files
              </p>
            )}

            <label className="mt-3">
              <input
                type="file"
                className="hidden"
                accept={acceptedTypes}
                onChange={handleFileChange}
                disabled={isLoading}
              />
              <span
                className={`
                inline-block 
                px-3 
                py-1.5 
                rounded-md 
                text-white
                text-sm
                bg-blue-600 
                hover:bg-blue-700 
                cursor-pointer
                transition-colors
                ${isLoading ? "opacity-50 cursor-not-allowed" : ""}
              `}
              >
                Select File
              </span>
            </label>
          </>
        )}
      </div>
    </div>
  );
};

export default FileUploader;
