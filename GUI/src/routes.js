import React from 'react';
import { Route, IndexRoute } from 'react-router';

/**
 * Import all page components here
 */
import App from './App';
import WelcomePage from './components/WelcomePage';
import GenerateSettings from './components/GenerateSettings';
import DrawGraph from './components/DrawGraph';

/**
 * All routes go here.
 * Don't forget to import the components above after adding new route.
 */
export default (
    <Route path="/" component={ App }>
        <IndexRoute component={ WelcomePage } />
        <Route path="/genSettings" component={ GenerateSettings } />
        <Route path="/drawGraph" component={ DrawGraph } />
    </Route>
);