import React from "react";

class Form extends React.Component {
    constructor (props) {
        super(props);
        this.state = {
            boardname: '',
            hivename: '',
            time_to_send: 0,
        };
    }

    onSubmit = (event) => {
        if (event) {
            event.preventDefault();
        }

        // Download
        const element = document.createElement("a");
        let file = new Blob([JSON.stringify(this.state)], { type: 'txt' });
        element.href = URL.createObjectURL(file)
        element.download = 'settings.txt'
        document.body.appendChild(element)
        element.click()
        this.props.handler();
    };

    onChange = (event) => {
        event.persist();

        let name = event.target.name;
        let value = event.target.value;

        if (name === 'time_to_send') {
            this.setState({
                time_to_send: parseInt(value)
            });
        }
        else {
            this.setState({
                [name]: value
            });
        }
    };

    render () {
        return (
            <>
                <h3>Welcome! Create a new file for the device.</h3>
                <form onSubmit={ this.onSubmit }>
                    <div className="field">
                        <input name="boardname" className="input" placeholder=" " onChange={ this.onChange } />
                        <label htmlFor="boardname" className="label">Board Name</label>
                    </div>

                    <div className="field">
                        <input type='text' name="hivename" className="input" placeholder=" " onChange={ this.onChange } />
                        <label htmlFor="hivename" className="label">Hive Name</label>
                    </div>

                    <div className="field">
                        <input type='text' pattern="[0-9]*" name="time_to_send" className="input" placeholder=" " onChange={ this.onChange } />
                        <label htmlFor="time_to_send" className="label">Time In Minutes</label>
                    </div>

                    <div className="button1">
                        <button disabled={ !this.state.boardname.length || !this.state.hivename.length || !this.state.time_to_send } onClick={ this.onSubmit }>Submit</button>
                    </div>
                </form></>
        );
    }
}

export default Form;