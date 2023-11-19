function clickHandler(id) {
    sendMessage('get_attack_positions|' + id)
        .then(() => highlighAttackPositions())
        .catch((error) => console.error('Error:', error));
}

function highlighAttackPositions(){
    if (getLastReceivedData() != undefined){
        for (let i = 1; i < 9; i++){
            for (let j = 1; j < 9; j++){
                let cage = document.getElementById(String(i) + '_' + String(j))
                cage.classList.remove('attack_position')
            }
        }
        setAttackPosition(getLastReceivedData())
        console.log('attack positions', getLastReceivedData())
        getLastReceivedData().forEach(array => {
            i = array[0]
            j = array[1]
            cage = document.getElementById(String(i) + '_' + String(j))
            cage.classList.add('attack_position')
        });
        console.log('attack positions', getAttackPositions())
    }
}