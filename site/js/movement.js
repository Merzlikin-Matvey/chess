function clickHandler(id) {
    previousReceivedData = getLastReceivedData()
    if (previousReceivedData != null){
        console.log(previousReceivedData)
        if (previousReceivedData.some(
                arr => arr[0] == Number(id[0]) && arr[1] == Number(id[2]))
            ){
                console.log(getLastReceivedData())
                sendMessage('move|' + getSelectedPosition() + '|' + id)
                .then(() => move())
        }
        else{
            setSelectedPosition(id)
            sendMessage('get_attack_positions|' + id)
            .then(() => highlighAttackPositions())
            .catch((error) => console.error('Error:', error));
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
        getLastReceivedData().forEach(array => {
            i = array[0]
            j = array[1]
            cage = document.getElementById(String(i) + '_' + String(j))
            cage.classList.add('attack_position')
        });
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

function move(){
    let x1 = getSelectedPosition()[0]
    let y1 = getSelectedPosition()[2]
    let x2 = getLastReceivedData().split('|')[2].split('_')[0]
    let y2 = getLastReceivedData().split('|')[2].split('_')[1]

    let oldCage = document.getElementById(x1 + '_' + y1)
    let images = oldCage.getElementsByTagName('img');

    if (images.length != 0) {
        oldCage.removeChild(images[0]);
    }

    let newCage = document.getElementById(x2 + '_' + y2)
    images = newCage.getElementsByTagName('img');

    if (images.length != 0) {
        newCage.removeChild(images[0]);
    }

    let img = document.createElement('img')
    let color = getLastReceivedData().split('|')[0].toLowerCase()
    let name = getLastReceivedData().split('|')[1].toLowerCase()

    img.src = 'site/res/' + color + '_' + name +'.png'
    img.classList.add('figure-image');
    newCage.appendChild(img)

    removeHighlighPositions()

    if (getLastReceivedData().includes('checkmate')){
        console.log('конец')
        window.location.href = ""
    }

    setLastReceivedData(null)
}