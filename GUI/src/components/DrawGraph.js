import React, {useEffect, useState} from 'react';
import { Chart as ChartJS, registerables } from 'chart.js';
import { Line } from 'react-chartjs-2';
ChartJS.register(...registerables);

const DrawGraph = (props) => {
    const [Data, setData] = useState();

    useEffect(() => {
        const data1 = {
            labels: props.dataset['Date'],
            datasets: [
                {
                    label: props.name,
                    fill: false,
                    lineTension: 0.1,
                    backgroundColor: 'rgba(75,192,192,0.4)',
                    borderColor: 'rgba(75,192,192,1)',
                    borderCapStyle: 'butt',
                    borderDash: [],
                    borderDashOffset: 0.0,
                    borderJoinStyle: 'miter',
                    pointBorderColor: 'rgba(75,192,192,1)',
                    pointBackgroundColor: '#fff',
                    pointBorderWidth: 1,
                    pointHoverRadius: 5,
                    pointHoverBackgroundColor: 'rgba(75,192,192,1)',
                    pointHoverBorderColor: 'rgba(220,220,220,1)',
                    pointHoverBorderWidth: 2,
                    pointRadius: 5,
                    pointHitRadius: 10,
                    data: props.dataset[props.name],
                }
            ]
        };
        
        setData(data1);
    }, [props.name]);

    return (
        <>
            { Data && props.name ? 
                <div className="chart-container" style={ { position: 'relative', height: '75%', width: '75%', marginLeft: '10%' }}>
                    <Line data={Data} />
                </div>   
            : null
            }
        </>
    );
};

export default DrawGraph;