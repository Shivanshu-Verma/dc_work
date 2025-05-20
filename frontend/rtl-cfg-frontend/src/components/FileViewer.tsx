import React from 'react';
import { File, Loader2 } from 'lucide-react';
import { useTheme } from '../context/ThemeContext';

interface FileViewerProps {
  content: string | null;
  fileName: string | null;
  fileType: string | null;
  isLoading: boolean;
}

const FileViewer: React.FC<FileViewerProps> = ({ 
  content, 
  fileName, 
  fileType,
  isLoading 
}) => {
  const { theme } = useTheme();
  const [loadingProgress, setLoadingProgress] = React.useState(0);

  // Simulate progress when loading
  React.useEffect(() => {
    if (isLoading) {
      setLoadingProgress(0);
      const interval = setInterval(() => {
        setLoadingProgress(prev => {
          const next = prev + Math.random() * 15;
          return next > 90 ? 90 : next;
        });
      }, 200);
      
      return () => {
        clearInterval(interval);
        setLoadingProgress(100);
      };
    }
  }, [isLoading]);

  // Format the content based on file type
  const formattedContent = React.useMemo(() => {
    if (!content) return null;
    
    try {
      if (fileType === 'application/json') {
        // Pretty print JSON
        const parsedJson = JSON.parse(content);
        return JSON.stringify(parsedJson, null, 2);
      }
      // CSV could be formatted as a table, but for simplicity we're just showing raw content
      return content;
    } catch (e) {
      return content; // Fall back to raw content if formatting fails
    }
  }, [content, fileType]);

  const containerClasses = `
    rounded-xl 
    border
    h-80
    transition-colors 
    duration-200
    ${theme === 'dark' ? 'bg-slate-800 border-slate-700' : 'bg-white border-slate-200'}
  `;

  return (
    <div className="h-full">
      <h2 className="text-xl font-semibold mb-4">File Content</h2>
      
      <div className={containerClasses}>
        {isLoading ? (
          <div className="flex flex-col items-center justify-center h-full text-center p-6">
            <Loader2 className="h-12 w-12 text-blue-500 animate-spin mb-4" />
            <p className="text-lg font-medium mb-4">Processing your file...</p>
            <div className="w-full max-w-md bg-slate-200 dark:bg-slate-700 rounded-full h-2.5 mb-2">
              <div 
                className="bg-blue-500 h-2.5 rounded-full transition-all duration-300 ease-out"
                style={{ width: `${loadingProgress}%` }}
              />
            </div>
            <p className="text-sm text-slate-500 dark:text-slate-400">
              {Math.round(loadingProgress)}% complete
            </p>
          </div>
        ) : content ? (
          <div className="h-full flex flex-col">
            {fileName && (
              <div className={`
                px-4 
                py-2 
                border-b 
                flex 
                items-center 
                gap-2
                ${theme === 'dark' ? 'border-slate-700 bg-slate-700' : 'border-slate-200 bg-slate-50'}
              `}>
                <File className="h-4 w-4 text-blue-500" />
                <span className="font-medium truncate">{fileName}</span>
              </div>
            )}
            <div className="flex-1 overflow-auto p-4">
              <pre className={`
                font-mono 
                text-sm 
                whitespace-pre-wrap 
                h-full
                ${theme === 'dark' ? 'text-slate-300' : 'text-slate-800'}
              `}>
                {formattedContent}
              </pre>
            </div>
          </div>
        ) : (
          <div className="flex flex-col items-center justify-center h-full text-center p-6">
            <div className={`
              rounded-full 
              p-4 
              mb-4
              ${theme === 'dark' ? 'bg-slate-700' : 'bg-slate-100'}
            `}>
              <File className="h-8 w-8 text-blue-500" />
            </div>
            <p className="text-lg font-medium mb-2">
              No file selected
            </p>
            <p className="text-sm text-slate-500 dark:text-slate-400 max-w-xs">
              Upload a file to see its contents displayed here
            </p>
          </div>
        )}
      </div>
    </div>
  );
};

export default FileViewer;