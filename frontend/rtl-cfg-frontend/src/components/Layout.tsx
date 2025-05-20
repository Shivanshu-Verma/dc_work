import React from "react";
import Header from "./Header";
import { useTheme } from "../context/ThemeContext";

interface LayoutProps {
  children: React.ReactNode;
}

const Layout: React.FC<LayoutProps> = ({ children }) => {
  const { theme } = useTheme();

  return (
    <div
      className={`min-h-screen transition-colors duration-200 ${
        theme === "dark"
          ? "bg-slate-900 text-white"
          : "bg-blue-50 text-slate-900"
      }`}
    >
      <Header />
      <main className="container mx-auto px-4 py-8">{children}</main>
      <footer
        className={`py-4 text-center text-sm ${
          theme === "dark" ? "text-slate-400" : "text-slate-600"
        }`}
      >
        <p>
          RTL to CFG Converter and Graph Visualizer © {new Date().getFullYear()}
          . All Rights Reserved.
        </p>
        <p>
          Made with 💙 by{" "}
          <a
            href={import.meta.env.VITE_AUTHOR1_URL}
            target="_blank"
            rel="noopener noreferrer"
            className="text-blue-500 hover:underline"
          >
            Avanti Mittal (B22ES021)
          </a>{" "}
          and{" "}
          <a
            href={import.meta.env.VITE_AUTHOR2_URL}
            target="_blank"
            rel="noopener noreferrer"
            className="text-blue-500 hover:underline"
          >
            Shivanshu Verma (B22ES010)
          </a>
          .
        </p>
      </footer>
    </div>
  );
};

export default Layout;
