function clickHandler(id) {
    previousReceivedData = getLastReceivedData()


    if (previousReceivedData != null){
        if (previousReceivedData.some(
                arr => arr[0] == Number(id[0]) && arr[1] == Number(id[2]))
            ){
                sendMessage('move|' + getSelectedPosition() + '|' + id)
        }
    }
    else{
        setSelectedPosition(id)
        sendMessage('get_attack_positions|' + id)
        .then(() => highlighAttackPositions())
        .catch((error) => console.error('Error:', error));
    }

}

function highlighAttackPositions(){
    if (getLastReceivedData() != undefined){
        removeHighlighPositions()
        setAttackPositions(getLastReceivedData())
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

function removeHighlighPositions(){
    for (let i = 1; i < 9; i++){
        for (let j = 1; j < 9; j++){
            let cage = document.getElementById(String(i) + '_' + String(j))
            cage.classList.remove('attack_position')
        }
    }
}