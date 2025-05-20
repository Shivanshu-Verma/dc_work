import React from "react";
import { Sun, Moon, FileText } from "lucide-react";
import { useTheme } from "../context/ThemeContext";

const Header: React.FC = () => {
  const { theme, toggleTheme } = useTheme();

  return (
    <header
      className={`py-4 px-6 ${
        theme === "dark" ? "bg-slate-800" : "bg-white"
      } shadow-md transition-colors duration-200`}
    >
      <div className="container mx-auto flex items-center justify-between">
        <div className="flex items-center gap-2">
          <FileText className="h-6 w-6 text-blue-600" />
          <h1 className="text-xl font-semibold">
            RTL to CFG Converter and Graph Visualizer
          </h1>
        </div>

        <button
          onClick={toggleTheme}
          className={`p-2 rounded-full transition-colors ${
            theme === "dark"
              ? "bg-slate-700 hover:bg-slate-600"
              : "bg-slate-100 hover:bg-slate-200"
          }`}
          aria-label={
            theme === "dark" ? "Switch to light mode" : "Switch to dark mode"
          }
        >
          {theme === "dark" ? (
            <Sun className="h-5 w-5 text-yellow-400" />
          ) : (
            <Moon className="h-5 w-5 text-slate-700" />
          )}
        </button>
      </div>
    </header>
  );
};

export default Header;
