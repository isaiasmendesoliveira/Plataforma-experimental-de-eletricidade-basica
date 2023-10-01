/*

Códigos JavaScript
Isaias Mendes de Oliveira
Experimento Remoto
2022
    
*/
var conexao = new WebSocket('ws://'+location.hostname+':81/', ['arduino']);
var Valor;
var Teste;

conexao.onopen = function ()
  {
    conexao.send('Conectado ' + new Date());
  };
conexao.onerror = function (error)
  {
    console.log('Erro de conexão do WebSocket ', error);
  };
conexao.onmessage = function (e)
  {  
    console.log('Servidor: ', e.data);
  };
conexao.onclose = function()
  {
    console.log('Conexão WebSocket finalizada');
  };

  var Ch1Status = 0;
  var Ch2Status = 0;
  var Ch3Status = 0;
  var Ch4Status = 0;
  var Ch5Status = 0;
  var Ch6Status = 0;
  var Ch7Status = 0;
  var Ch8Status = 0;

  function CriarCircuito(Objeto)
  {
    for (var i = 0; i < Objeto.length; i++) {
             console.log(Objeto[i]);
           }
  };

    function MudarCor(Id){
        
        document.getElementById("la01").style.fill = '#FAFAFA';
        document.getElementById("la02").style.fill = '#FAFAFA';
        document.getElementById("la03").style.fill = '#FAFAFA';
        document.getElementById("la04").style.fill = '#FAFAFA';

        document.getElementById("liv01").style.stroke = "#000000";
        document.getElementById("liv02").style.stroke = "#000000";
        document.getElementById("liv03").style.stroke = "#000000";
        document.getElementById("liv04").style.stroke = "#000000";
        document.getElementById("liv05").style.stroke = "#000000";
        document.getElementById("liv06").style.stroke = "#000000";
        document.getElementById("liv07").style.stroke = "#000000";
        document.getElementById("liv08").style.stroke = "#000000";
        document.getElementById("liv09").style.stroke = "#000000";
        document.getElementById("liv10").style.stroke = "#000000";
        document.getElementById("liv11").style.stroke = "#000000";
        document.getElementById("liv12").style.stroke = "#000000";
        document.getElementById("liv13").style.stroke = "#000000";
        document.getElementById("liv14").style.stroke = "#000000";
        document.getElementById("liv15").style.stroke = "#000000";
        document.getElementById("liv16").style.stroke = "#000000";
        document.getElementById("liv17").style.stroke = "#000000";

        document.getElementById("lih01").style.stroke = "#000000";
        document.getElementById("lih02").style.stroke = "#000000";
        document.getElementById("lih03").style.stroke = "#000000";
        document.getElementById("lih04").style.stroke = "#000000";
        document.getElementById("lih05").style.stroke = "#000000";
        document.getElementById("lih06").style.stroke = "#000000";
        document.getElementById("lih07").style.stroke = "#000000";
        document.getElementById("lih08").style.stroke = "#000000";
        document.getElementById("lih09").style.stroke = "#000000";
        document.getElementById("lih10").style.stroke = "#000000";
        document.getElementById("lih11").style.stroke = "#000000";
        document.getElementById("lih12").style.stroke = "#000000";
        document.getElementById("lih13").style.stroke = "#000000";
        document.getElementById("lih14").style.stroke = "#000000";
        document.getElementById("lih15").style.stroke = "#000000";

        document.getElementById("po01").style.fill = "#000000";
        document.getElementById("po02").style.fill = "#000000";
        document.getElementById("po03").style.fill = "#000000";
        document.getElementById("po04").style.fill = "#000000";
        document.getElementById("po05").style.fill = "#000000";
        document.getElementById("po06").style.fill = "#000000";
        document.getElementById("po07").style.fill = "#000000";
        document.getElementById("po08").style.fill = "#000000";
        document.getElementById("po09").style.fill = "#000000";
        document.getElementById("po10").style.fill = "#000000";
        document.getElementById("po11").style.fill = "#000000";
        document.getElementById("po12").style.fill = "#000000";



      switch(Id){
        case 'ch01':
          if (Ch1Status==0){
            document.getElementById(Id).style.fill = "#00ff0066";
            document.getElementById('abr01').style.display = "none";
            document.getElementById('fec01').style.display = "block";
            Ch1Status = 1;
            conexao.send("C1L");
           }else{
            document.getElementById(Id).style.fill = "#ff000066";
            document.getElementById('abr01').style.display = "block";
            document.getElementById('fec01').style.display = "none";
            Ch1Status = 0;
            conexao.send("C1D");
          }
          break;
        case 'ch02':
          if (Ch2Status==0){
            document.getElementById(Id).style.fill = "#00ff0066";
            document.getElementById('abr02').style.display = "none";
            document.getElementById('fec02').style.display = "block";
            Ch2Status = 1;
            conexao.send("C2L");
          }else{
            document.getElementById(Id).style.fill = "#ff000066";
            document.getElementById('abr02').style.display = "block";
            document.getElementById('fec02').style.display = "none";
            Ch2Status = 0;
            conexao.send("C2D");
          }
          break;
        case 'ch03':
          if (Ch3Status==0){
            document.getElementById(Id).style.fill = "#00ff0066";
            document.getElementById('abr03').style.display = "none";
            document.getElementById('fec03').style.display = "block";
            Ch3Status = 1;
            conexao.send("C3L");
          }else{
            document.getElementById(Id).style.fill = "#ff000066";
            document.getElementById('abr03').style.display = "block";
            document.getElementById('fec03').style.display = "none";
            Ch3Status = 0;
            conexao.send("C3D");
          }
          break;
        case 'ch04':
          if (Ch4Status==0){
            document.getElementById(Id).style.fill = "#00ff0066";
            document.getElementById('abr04').style.display = "none";
            document.getElementById('fec04').style.display = "block";
            Ch4Status = 1;
            conexao.send("C4L");
          }else{
            document.getElementById(Id).style.fill = "#ff000066";
            document.getElementById('abr04').style.display = "block";
            document.getElementById('fec04').style.display = "none";
            Ch4Status = 0;
            conexao.send("C4D");
          }
          break;
        case 'ch05':
          if (Ch5Status==0){
            document.getElementById(Id).style.fill = "#00ff0066";
            document.getElementById('abr05').style.display = "none";
            document.getElementById('fec05').style.display = "block";
            Ch5Status = 1;
            conexao.send("C5L");
          }else{
            document.getElementById(Id).style.fill = "#ff000066";
            document.getElementById('abr05').style.display = "block";
            document.getElementById('fec05').style.display = "none";
            Ch5Status = 0;
            conexao.send("C5D");
          }
          break;
        case 'ch06':
          if (Ch6Status==0){
            document.getElementById(Id).style.fill = "#00ff0066";
            document.getElementById('abr06').style.display = "none";
            document.getElementById('fec06').style.display = "block";
            Ch6Status = 1;
            conexao.send("C6L");
          }else{
            document.getElementById(Id).style.fill = "#ff000066";
            document.getElementById('abr06').style.display = "block";
            document.getElementById('fec06').style.display = "none";
            Ch6Status = 0;
            conexao.send("C6D");
          }
          break;
        case 'ch07':
          if (Ch7Status==0){
            document.getElementById(Id).style.fill = "#00ff0066";
            document.getElementById('abr07').style.display = "none";
            document.getElementById('fec07').style.display = "block";
            Ch7Status = 1;
            conexao.send("C7L");
          }else{
            document.getElementById(Id).style.fill = "#ff000066";
            document.getElementById('abr07').style.display = "block";
            document.getElementById('fec07').style.display = "none";
            Ch7Status = 0;
            conexao.send("C7D");
          }
          break;
        case 'ch08':
          if (Ch8Status==0){
            document.getElementById(Id).style.fill = "#00ff0066";
            document.getElementById('abr08').style.display = "none";
            document.getElementById('fec08').style.display = "block";
            Ch8Status = 1;
            conexao.send("C8L");
          }else{
             document.getElementById(Id).style.fill = "#ff000066";
            document.getElementById('abr08').style.display = "block";
            document.getElementById('fec08').style.display = "none";
            Ch8Status = 0;
            conexao.send("C8D");
          }
          break;
      }
        // Circuito Equivalente 01
      if (Ch1Status==1 && Ch2Status==1 && Ch3Status==1 && Ch4Status==1 && Ch5Status==1 && Ch6Status==1 && Ch7Status==1 && Ch8Status==1){
        document.getElementById("la01").style.fill = '#FFFF00';
        document.getElementById("la02").style.fill = '#FFFF00';
        document.getElementById("la03").style.fill = '#FFFF00';
        document.getElementById("la04").style.fill = '#FFFF00';

        document.getElementById("liv01").style.stroke = "#0000FF";
        document.getElementById("liv02").style.stroke = "#0000FF";
        document.getElementById("liv03").style.stroke = "#0000FF";
        document.getElementById("liv04").style.stroke = "#0000FF";
        document.getElementById("liv05").style.stroke = "#0000FF";
        document.getElementById("liv06").style.stroke = "#0000FF";
        document.getElementById("liv07").style.stroke = "#0000FF";
        document.getElementById("liv08").style.stroke = "#0000FF";
        document.getElementById("liv09").style.stroke = "#0000FF";
        document.getElementById("liv10").style.stroke = "#0000FF";
        document.getElementById("liv11").style.stroke = "#0000FF";
        document.getElementById("liv12").style.stroke = "#0000FF";
        document.getElementById("liv13").style.stroke = "#0000FF";
        document.getElementById("liv14").style.stroke = "#0000FF";
        document.getElementById("liv15").style.stroke = "#0000FF";
        document.getElementById("liv16").style.stroke = "#0000FF";
        document.getElementById("liv17").style.stroke = "#0000FF";

        document.getElementById("lih01").style.stroke = "#0000FF";
        document.getElementById("lih02").style.stroke = "#0000FF";
        document.getElementById("lih03").style.stroke = "#0000FF";
        document.getElementById("lih04").style.stroke = "#0000FF";
        document.getElementById("lih05").style.stroke = "#0000FF";
        document.getElementById("lih06").style.stroke = "#0000FF";
        document.getElementById("lih07").style.stroke = "#0000FF";
        document.getElementById("lih08").style.stroke = "#0000FF";
        document.getElementById("lih09").style.stroke = "#0000FF";
        document.getElementById("lih10").style.stroke = "#0000FF";
        document.getElementById("lih11").style.stroke = "#0000FF";
        document.getElementById("lih12").style.stroke = "#0000FF";
        document.getElementById("lih13").style.stroke = "#0000FF";
        document.getElementById("lih14").style.stroke = "#0000FF";
        document.getElementById("lih15").style.stroke = "#0000FF";

        document.getElementById("po01").style.fill = "#0000FF";
        document.getElementById("po02").style.fill = "#0000FF";
        document.getElementById("po03").style.fill = "#0000FF";
        document.getElementById("po04").style.fill = "#0000FF";
        document.getElementById("po05").style.fill = "#0000FF";
        document.getElementById("po06").style.fill = "#0000FF";
        document.getElementById("po07").style.fill = "#0000FF";
        document.getElementById("po08").style.fill = "#0000FF";
        document.getElementById("po09").style.fill = "#0000FF";
        document.getElementById("po10").style.fill = "#0000FF";
        document.getElementById("po11").style.fill = "#0000FF";
        document.getElementById("po12").style.fill = "#0000FF";
      }

        // Circuito Equivalente 02
      if (Ch1Status==1 && Ch2Status==1 && Ch3Status==1 && Ch4Status==1 && Ch5Status==1 && Ch6Status==0 && Ch7Status==1 && Ch8Status==1){
        document.getElementById("la01").style.fill = '#FFFF00';
        document.getElementById("la02").style.fill = '#FFFF00';
        document.getElementById("la03").style.fill = '#FFFF00';
        document.getElementById("la04").style.fill = '#FAFAFA';

        document.getElementById("liv01").style.stroke = "#0000FF";
        document.getElementById("liv02").style.stroke = "#0000FF";
        document.getElementById("liv03").style.stroke = "#0000FF";
        document.getElementById("liv04").style.stroke = "#0000FF";
        document.getElementById("liv05").style.stroke = "#0000FF";
        document.getElementById("liv06").style.stroke = "#0000FF";
        document.getElementById("liv07").style.stroke = "#0000FF";
        document.getElementById("liv08").style.stroke = "#0000FF";
        document.getElementById("liv09").style.stroke = "#0000FF";
        document.getElementById("liv10").style.stroke = "#0000FF";
        document.getElementById("liv11").style.stroke = "#0000FF";
        document.getElementById("liv12").style.stroke = "#0000FF";
        document.getElementById("liv13").style.stroke = "#0000FF";
        document.getElementById("liv14").style.stroke = "#000000";
        document.getElementById("liv15").style.stroke = "#000000";
        document.getElementById("liv16").style.stroke = "#000000";
        document.getElementById("liv17").style.stroke = "#0000FF";

        document.getElementById("lih01").style.stroke = "#0000FF";
        document.getElementById("lih02").style.stroke = "#0000FF";
        document.getElementById("lih03").style.stroke = "#0000FF";
        document.getElementById("lih04").style.stroke = "#0000FF";
        document.getElementById("lih05").style.stroke = "#0000FF";
        document.getElementById("lih06").style.stroke = "#0000FF";
        document.getElementById("lih07").style.stroke = "#000000";
        document.getElementById("lih08").style.stroke = "#0000FF";
        document.getElementById("lih09").style.stroke = "#0000FF";
        document.getElementById("lih10").style.stroke = "#0000FF";
        document.getElementById("lih11").style.stroke = "#0000FF";
        document.getElementById("lih12").style.stroke = "#0000FF";
        document.getElementById("lih13").style.stroke = "#0000FF";
        document.getElementById("lih14").style.stroke = "#0000FF";
        document.getElementById("lih15").style.stroke = "#0000FF";

        document.getElementById("po01").style.fill = "#0000FF";
        document.getElementById("po02").style.fill = "#0000FF";
        document.getElementById("po03").style.fill = "#0000FF";
        document.getElementById("po04").style.fill = "#0000FF";
        document.getElementById("po05").style.fill = "#000000";
        document.getElementById("po06").style.fill = "#0000FF";
        document.getElementById("po07").style.fill = "#0000FF";
        document.getElementById("po08").style.fill = "#0000FF";
        document.getElementById("po09").style.fill = "#0000FF";
        document.getElementById("po10").style.fill = "#0000FF";
        document.getElementById("po11").style.fill = "#0000FF";
        document.getElementById("po12").style.fill = "#0000FF";
      }

    }
   




    conexao.onmessage = function(event) {

    Valor = event.data;
    var ValorDisplay = Valor.slice(0,2);

    switch (ValorDisplay){
        case "TU":
            document.getElementById("tu").innerHTML = "  " + (Valor.slice(2,Valor.length)).replace(".",",") + "V";
            break;
        case "CU":
            document.getElementById("cu").innerHTML = "  " + (Valor.slice(2,Valor.length)).replace(".",",") + "A";
            break;

        case "TD":
            document.getElementById("td").innerHTML = "  " + (Valor.slice(2,Valor.length)).replace(".",",") + "V";
            break;
        case "CD":
            document.getElementById("cd").innerHTML = "  " + (Valor.slice(2,Valor.length)).replace(".",",") + "A";
            break;

        case "TT":
            document.getElementById("tt").innerHTML = "  " + (Valor.slice(2,Valor.length)).replace(".",",") + "V";
            break;
        case "CT":
            document.getElementById("ct").innerHTML = "  " + (Valor.slice(2,Valor.length)).replace(".",",") + "A";
            break;

        case "TQ":
            document.getElementById("tq").innerHTML = "  " + (Valor.slice(2,Valor.length)).replace(".",",") + "V";
            break;
        case "CQ":
            document.getElementById("cq").innerHTML = "  " + (Valor.slice(2,Valor.length)).replace(".",",") + "A";
            break;
    }
    
    if (Valor=="N") {
        document.getElementById("disponivel").style.display="inline-block";
        document.getElementById("emuso").style.display="none";
        document.getElementById("espaco").style.display="none";
        Teste="N";
    }
    if (Valor=="S"){
        document.getElementById("disponivel").style.display="none";
        document.getElementById("emuso").style.display="inline-block";
        document.getElementById("espaco").style.display="none";
        Teste="S";
    }
   
    };


// CONTROLE DO MENU
function ControleMenu() {
    var x = document.getElementById("navDemo");
    if (x.className.indexOf("w3-show") == -1) {
      x.className += " w3-show";
    } else { 
      x.className = x.className.replace(" w3-show", "");
    }
  }
// FIM


// CONTROLE DO TEMPO
function Contador(duracao, exibicao) {
    var tempo = duracao, minutos, segundos;
    setInterval(function () {
        minutos = parseInt(tempo / 60, 10);
        segundos = parseInt(tempo % 60, 10);
        minutos = minutos < 10 ? "0" + minutos : minutos;
        segundos = segundos < 10 ? "0" + segundos : segundos;
        exibicao.textContent = minutos + ":" + segundos;
        if (--tempo < 0) {
            document.getElementById("tempo").style.display="none";
            document.getElementById("mensagem").style.display="inline-block";
            document.getElementById("mensagem").innerHTML="Tempo esgotado!! Você será redirecionado em 5 segundos";
            document.getElementById("disponivel").style.display="none";
            document.getElementById("emuso").style.display="none";
            var status = "N";
            var valor = status.toString();    
            console.log('Valor: ' + valor); 
            conexao.send(valor);
            conexao.send("C1D");
            conexao.send("C2D");
            conexao.send("C3D");
            conexao.send("C4D");
            conexao.send("C5D");
            conexao.send("C6D");
            conexao.send("C7D");
            conexao.send("C8D");
            setTimeout(function() {
                window.location.href = "index.html";
            }, 5000);
        }
    }, 1000);
}
function Tempo() {
    var duracao = 60 * 30; // Converter para segundos
    var exibicao = document.querySelector('#tempo'); // selecionando o timer
    Contador(duracao, exibicao); // iniciando o timer
}
// FIM

// EXIBIÇÃO DO EXPERIMENTO
function ExibirExperimento(){
    console.log(Teste);
     if (Teste=="S"){
        document.getElementById("mensagem").style.display="inline-block";
        document.getElementById("emuso").style.display="none";
        setTimeout(function() {
            document.getElementById("emuso").style.display="inline-block";
            document.getElementById("mensagem").style.display="none";
        }, 2000);
    }

    if (Teste=="N"){
        var status = "S";
        var valor = status.toString();    
        conexao.send(valor);
        document.getElementById("experimento").style.display="block";
        document.getElementById("menuexperimento").style.display="block";
        document.getElementById("menugeral").style.display="none";
        document.getElementById("conteudo").style.display="none";
        document.getElementById("video").src="http://192.168.0.151:81/stream";
        Tempo();
    }
   
    
}

function SairExperimento(){
    var status = "N";
    var valor = status.toString();    
    console.log('Valor: ' + valor); 
    conexao.send(valor);
    conexao.send("C1D");
    conexao.send("C2D");
    conexao.send("C3D");
    conexao.send("C4D");
    conexao.send("C5D");
    conexao.send("C6D");
    conexao.send("C7D");
    conexao.send("C8D");
    window.location.href = "index.html";
}

// FIM
