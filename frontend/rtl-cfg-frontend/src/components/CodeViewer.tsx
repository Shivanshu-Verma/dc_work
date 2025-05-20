import React, { useEffect, useRef } from "react";
import { useTheme } from "../context/ThemeContext";
import { Loader2 } from "lucide-react";
import Prism from "prismjs";
import "prismjs/themes/prism-tomorrow.css";
import { Copy } from "lucide-react";
import { ToastContainer, toast } from "react-toastify";
import "react-toastify/dist/ReactToastify.css";

interface CodeViewerProps {
  code: string | null; // DOT code
  fileName: string | null;
  isLoading: boolean;
}

const CodeViewer: React.FC<CodeViewerProps> = ({
  code,
  fileName,
  isLoading,
}) => {
  const { theme } = useTheme();
  const codeRef = useRef<HTMLPreElement>(null);

  useEffect(() => {
    if (code && codeRef.current) {
      Prism.highlightElement(codeRef.current);
    }
  }, [code]);

  const handleCopy = async () => {
    if (code) {
      // Try modern clipboard API first
      try {
        await navigator.clipboard.writeText(code);
        toast.success("Code copied to clipboard!", {
          position: "top-right",
          autoClose: 2000,
          hideProgressBar: false,
          closeOnClick: true,
          pauseOnHover: true,
          draggable: true,
          progress: undefined,
          theme: theme === "dark" ? "dark" : "light",
        });
        return;
      } catch (e) {
        // continue to fallback
      }
      // Fallback for mobile/unsupported browsers
      try {
        const textarea = document.createElement("textarea");
        textarea.value = code;
        textarea.style.position = "fixed"; // Prevent scrolling to bottom of page in MS Edge.
        textarea.style.opacity = "0";
        document.body.appendChild(textarea);
        textarea.focus();
        textarea.select();
        const successful = document.execCommand("copy");
        document.body.removeChild(textarea);
        if (successful) {
          toast.success("Code copied to clipboard!", {
            position: "top-right",
            autoClose: 2000,
            hideProgressBar: false,
            closeOnClick: true,
            pauseOnHover: true,
            draggable: true,
            progress: undefined,
            theme: theme === "dark" ? "dark" : "light",
          });
        } else {
          throw new Error();
        }
      } catch {
        toast.error(
          "Failed to copy code. Your browser may not support this feature."
        );
      }
    }
  };

  const containerClasses = `
    rounded-xl 
    border
    h-[300px]
    transition-colors 
    duration-200
    ${
      theme === "dark"
        ? "bg-slate-800 border-slate-700"
        : "bg-white border-slate-200"
    }
  `;

  return (
    <div>
      <h2 className="text-xl font-semibold mb-4">Processed Code</h2>
      <div className={containerClasses}>
        {isLoading ? (
          <div className="flex flex-col items-center justify-center h-full text-center p-4">
            <Loader2 className="h-8 w-8 text-blue-500 animate-spin mb-2" />
            <p className="text-sm font-medium">Processing code...</p>
          </div>
        ) : code ? (
          <div className="h-full flex flex-col">
            <div
              className={`
              px-3 
              py-1.5 
              border-b 
              flex 
              items-center 
              gap-2
              ${
                theme === "dark"
                  ? "border-slate-700 bg-slate-700"
                  : "border-slate-200 bg-slate-50"
              }
            `}
            >
              <span className="font-medium truncate text-sm">{fileName}</span>
              {code && (
                <button
                  onClick={handleCopy}
                  className="ml-auto p-1 rounded hover:bg-blue-100 dark:hover:bg-slate-600 transition-colors"
                  title="Copy code to clipboard"
                  aria-label="Copy code to clipboard"
                  type="button"
                >
                  <Copy className="h-4 w-4 text-blue-500" />
                </button>
              )}
            </div>
            <div className="flex-1 overflow-auto p-3">
              <pre ref={codeRef} className="language-none text-sm">
                <code>{code}</code>
              </pre>
            </div>
          </div>
        ) : (
          <div className="flex flex-col items-center justify-center h-full text-center p-4">
            <p className="text-sm font-medium mb-1">No code to display</p>
            <p className="text-xs text-slate-500 dark:text-slate-400">
              Upload a Verilog (.v) file to see the processed CFG code
            </p>
          </div>
        )}
      </div>
      <ToastContainer />
    </div>
  );
};

export default CodeViewer;
