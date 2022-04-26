import './App.css';
import React from 'react';
import { Routes, Route } from 'react-router-dom';

import Layout from './components/Layout';
import GenerateSettings from './components/GenerateSettings';
import NoPage from './components/NoPage';
import Import from './components/Import';
import Home from './components/Home';

class App extends React.Component {
  render () {
    return (
      <Routes>
        <Route path="/" element={ <Layout /> }>
          <Route index element={ <Home /> } />
          <Route path="generate" element={ <GenerateSettings /> } />
          <Route path="import" element={ <Import /> } />
          <Route path="*" element={ <NoPage /> } />
        </Route>
      </Routes>
    );
  }
}

export default App;
