import React from 'react';
import { ThemeProvider } from './context/ThemeContext';
import Layout from './components/Layout';
import FileProcessorView from './components/FileProcessorView';

function App() {
  return (
    <ThemeProvider>
      <Layout>
        <FileProcessorView />
      </Layout>
    </ThemeProvider>
  );
}

export default App;