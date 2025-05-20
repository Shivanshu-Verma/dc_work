/**
 * Determines if a file is of a supported type
 */
export const isSupportedFileType = (file: File): boolean => {
  const validTypes = ["text/csv", "text/plain", "application/json"];
  return validTypes.includes(file.type) || file.name.endsWith(".csv");
};

/**
 * Formats file sizes in a human-readable way
 */
export const formatFileSize = (bytes: number): string => {
  if (bytes === 0) return "0 Bytes";

  const k = 1024;
  const sizes = ["Bytes", "KB", "MB", "GB"];
  const i = Math.floor(Math.log(bytes) / Math.log(k));

  return parseFloat((bytes / Math.pow(k, i)).toFixed(2)) + " " + sizes[i];
};

/**
 * Try to determine if content is JSON
 */
export const isJsonString = (str: string): boolean => {
  try {
    JSON.parse(str);
    return true;
  } catch (e) {
    return false;
  }
};

/**
 * Try to format content based on detected type
 */
export const formatContent = (
  content: string,
  fileType: string | null
): string => {
  // If it's JSON or looks like JSON, pretty print it
  if (fileType === "application/json" || isJsonString(content)) {
    try {
      const parsed = JSON.parse(content);
      return JSON.stringify(parsed, null, 2);
    } catch {
      // If parsing fails, return as is
      return content;
    }
  }

  // For now, we return other content types as-is
  // Additional formatters could be added for CSV, etc.
  return content;
};
