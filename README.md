# BreakoutGame

O jogo deve ser jogado com o teclado.

-A seta Right faz com que a barra se descloque para a direita, e a seta Left faz com que a barra se desloque pela esquerda.

Haverá sons quando a bola encosta na barra e quando a bola enconsta no tijolo.

-O tijolo deve ser encostado 2 vezes pela bola para que seja destruído. A primeira cor é azul e a segunda laranja.

-Uma decisão de projeto foi a inclusão na primeira fase (somente) das bombas. Ao ser encostada ela faz com que as bombas vizinhas desative, caso tenha,
e faz com que os tijolos percam "1 vida". Ou seja, se ele estiver laranja é destruída, se estiver azul vira laranja.

-A opção menu pode ser acessada no Widget menu ou clicando com o lado esquerdo do mouse. Em ambos os casos, aparecerá a posição XY da bola e da barra. Ambos em relação aos limites do jogo, e não em relação ao Widget completo (Ver que na função ball e paddle fazemos um deslocamento em rect.x()).

Ao passar de level (2 em diante) a velocidade irá dobrar e não haverá mais a opção de bombas.

As opções bonus escolhidas são:

1) Melhorar a interface.
3) Acrescentar música e sons ao jogo.
5) Tijolos podem não quebrar diretamente.
6) Acrescentar níveis de dificuldade.
7) Alguns tijolos podem ter bônus. (Foi escolhido a bomba).





