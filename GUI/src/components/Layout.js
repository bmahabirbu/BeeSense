import React from "react";
import { Link, Outlet } from "react-router-dom";

const Layout = () => {
    return (
        <>
            <nav className="navbar">
                <ul className="navbar-nav">
                    <li className="listItem">
                        <Link to="/">
                            <text>Home</text>
                        </Link>
                    </li>
                    <li className="listItem">
                        <Link className="Link" to="/generate">
                            <text>Generate Settings</text>
                        </Link>
                    </li>
                    <li className="listItem">
                        <Link to="/import">
                            <text>Import CSV</text>
                        </Link>
                    </li>
                </ul>
            </nav>

            <Outlet />
        </>
    )
}


export default Layout;