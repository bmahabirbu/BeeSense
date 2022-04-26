import logo from '../assets/Bee.png';

const Home = () => {
    return (
        <>
            <div className='logo'>
                <img src={ logo } alt='Bee' />
            </div>
            <h3>Welcome to BeeSense</h3>
        </>
    );
};

export default Home;