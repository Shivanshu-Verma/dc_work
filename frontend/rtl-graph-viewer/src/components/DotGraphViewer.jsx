// DotGraphViewer.jsx
import React, { useEffect, useRef, useState } from "react";
import { Graphviz } from "@hpcc-js/wasm-graphviz"; // import Graphviz from new package
import axios from "axios";

function DotGraphViewer() {
  const containerRef = useRef(null);
  const [dotCode, setDotCode] = useState(null);
  const [error, setError] = useState(null);
  const [fileName, setFileName] = useState("graph");
  const [graphvizInstance, setGraphvizInstance] = useState(null);

  // Load graphviz once on mount
  useEffect(() => {
    Graphviz.load()
      .then((graphviz) => {
        setGraphvizInstance(graphviz);
      })
      .catch((err) => {
        console.error("Failed to load Graphviz:", err);
        setError("Failed to load Graphviz.");
      });
  }, []);

  const handleUpload = async (event) => {
    const file = event.target.files[0];
    if (!file) return;

    const formData = new FormData();
    formData.append("rtl_file", file);
    setFileName(file.name.replace(/\.[^/.]+$/, ""));

    try {
      const response = await axios.post(
        `${import.meta.env.VITE_API_URL}/api/convert/`,
        formData
      );
      setDotCode(response.data.dot);
      setError(null);
    } catch (err) {
      setError("Error uploading file or generating DOT graph.");
      console.error(err);
    }
  };

  const handleDownload = () => {
    if (!containerRef.current) return;
    const svg = containerRef.current.innerHTML;
    const blob = new Blob([svg], { type: "image/svg+xml" });
    const url = URL.createObjectURL(blob);
    const a = document.createElement("a");
    a.href = url;
    a.download = `${fileName}.svg`;
    a.click();
    URL.revokeObjectURL(url);
  };

  useEffect(() => {
    if (dotCode && graphvizInstance && containerRef.current) {
      try {
        // Render the dot code to svg using graphviz.dot
        const svg = graphvizInstance.dot(dotCode);
        containerRef.current.innerHTML = svg;
        setError(null);
      } catch (err) {
        console.error("Error rendering DOT graph:", err);
        setError("Failed to render graph.");
        containerRef.current.innerHTML = "";
      }
    }
  }, [dotCode, graphvizInstance]);

  return (
    <div style={{ padding: "1rem", fontFamily: "Arial" }}>
      <h2>RTL CFG Graph Viewer</h2>
      <input type="file" accept=".v" onChange={handleUpload} />
      {error && <p style={{ color: "red" }}>{error}</p>}
      {dotCode && (
        <button onClick={handleDownload} style={{ marginTop: "1rem" }}>
          Download SVG
        </button>
      )}
      <div
        ref={containerRef}
        style={{
          marginTop: "2rem",
          border: "1px solid #ccc",
          padding: "1rem",
          overflowX: "auto",
        }}
      ></div>
    </div>
  );
}

export default DotGraphViewer;
