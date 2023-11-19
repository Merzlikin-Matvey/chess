function clickHandler(id) {
    sendMessage('get_attack_positions|' + id)
        .then(() => getAttackPositions())
        .catch((error) => console.error('Error:', error));
}

function getAttackPositions(){
    if (getLastReceivedData() != undefined){
        for (let i = 1; i < 9; i++){
            for (let j = 1; j < 9; j++){
                let cage = document.getElementById(String(i) + '_' + String(j))
                cage.classList.remove('attack_position')
            }
        }
        console.log('attack positions', getLastReceivedData())
        getLastReceivedData().forEach(array => {
            i = array[0]
            j = array[1]
            cage = document.getElementById(String(i) + '_' + String(j))
            cage.classList.add('attack_position')
        });
    }
}