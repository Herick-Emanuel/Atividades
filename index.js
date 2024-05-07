const somar = (numero1, numero2) => {
    numero1 = document.getElementById('numero1').value
    numero2 = document.getElementById('numero2').value

    numero3 = document.getElementById("numero3")

    numero3.innerText = `resultado: ${parseInt(numero1) + parseInt(numero2)}`

}