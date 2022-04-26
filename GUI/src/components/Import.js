import React, { useState, useEffect } from "react";
import DrawGraph from "./DrawGraph";

const Import = () => {
    const [file, setFile] = useState();
    const [headers, setHeaders] = useState([]);
    const [array, setArray] = useState([]);
    const [dataset, setDataset] = useState();
    const [currentHeader, setCurrentHeader] = useState('')

    useEffect(() => {
        if (headers.length) {
            const data = {};
            for (const header of headers) {
                data[header] = []
            }

            for (let i = 0; i < array.length - 1; i++) {
                // console.log(elem);
                for (const [key, value] of Object.entries(array[i])) {
                    // console.log(name);
                    if (key === 'Date') {
                        data[key].push(value)
                    }
                    else {
                        data[key].push(parseFloat(value));
                    }
                }
            }

            const index = headers.indexOf('Date');
            if (index > -1) {
                headers.splice(index, 1); // 2nd parameter means remove one item only
            }

            setDataset(data);
        }
    }, [headers]);
    

    const fileReader = new FileReader();

    const handleOnChange = (e) => {
        setFile(e.target.files[0]);
        console.log(e.target.files[0]);
    };

    const csvFileToArray = string => {
        const csvHeader = string.slice(0, string.indexOf("\n")).split(",");
        const csvRows = string.slice(string.indexOf("\n") + 1).split("\n");
        
        const array = csvRows.map(i => {
            const values = i.split(",");
            const obj = csvHeader.reduce((object, header, index) => {
                object[header] = values[index];
                return object;
            }, {});
            return obj;
        });
        
        setArray(array);
        setHeaders(csvHeader);
    };

    const handleOnSubmit = (e) => {
        e.preventDefault();

        if (file) {
            fileReader.onload = function (event) {
                const text = event.target.result;
                csvFileToArray(text);
            };
            fileReader.readAsText(file);
        }
    };

    return (
        <>
            <h3>CSV VISUALISATION</h3>
            
            { dataset ?
                <>
                    <div className="dropdown">
                        <button className="dropbtn">Select A Graph</button>
                        <div className="dropdown-content">
                            { headers.map(header => {
                                return (
                                    <a key={ header } onClick={ () => { setCurrentHeader(header); } }>{ header }</a>
                                );
                            })}
                        </div>
                    </div>

                    <DrawGraph
                        dataset={ dataset }
                        name={ currentHeader }  
                    />
                    
                    <div className="redo" style={{ marginBottom: '10%', marginLeft:'1%' }}>
                        <button onClick={ () => { setDataset(null) } }>Upload A Different File</button>
                    </div>
                </>
                :
                <form className="fileUpload">
                    <div>
                        {/* <input
                            className="fileInput"
                            type={ "file" }
                            id={ "csvFileInput" }
                            accept={ ".csv" }
                            onChange={ handleOnChange } 
                        /> */}
                        <label className="custom-file-upload">
                            <input
                                type={ 'file' }
                                id={ "csvFileInput" }
                                accept={ ".csv" }
                                onChange={ handleOnChange }
                            />
                            {file ? file.name : 'Upload Your CSV Here'}
                        </label>
                    </div>

                    <button disabled={!file} style={ { marginLeft: '1%' }} onClick={ (e) => { handleOnSubmit(e) } }>IMPORT CSV</button>
                </form>
            }
        </>
    );
};

export default Import;
