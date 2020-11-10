#ifndef _SERVER_H
#define _SERVER_H

#define CANT_CHALLENGES 12

char *challenges[CANT_CHALLENGES] = {
    "Bienvenidos al TP3 y felicitaciones, ya resolvieron el primer acertijo.\n\nEn este TP deberán finalizar el juego que ya comenzaron resolviendo los desafíos de cada nivel.\nAdemás tendrán que investigar otras preguntas para responder durante la defensa.\nEl desafío final consiste en crear un programa que se comporte igual que yo, es decir, que provea los mismos desafíos y que sea necesario hacer lo mismo para resolverlos.No basta con esperar la respuesta.\nAdemás, deberán implementar otro programa para comunicarse conmigo.\n\nDeberán estar atentos a los easter eggs.\n\nPara verificar que sus respuestas tienen el formato correcto respondan a este desafío con la palabra 'entendido\\n'",
    "The Wire S1E5\n5295 888 6288",
    "https://ibb.co/tc0Hb6w",
    "EBADF...",
    "respuesta = strings:277",
    ".data .bss .comment ? .shstrtab .symtab .strtab",
    "Filter error",
    "¿?",
    "Si\n\mathrm{d}y = u^v{\cdot}(v'{\cdot}\ln{(u)}+v{\cdot}\\frac{u'}{u})\nentonces\ny = ",
    "quine",
    "b gdbme y encontrá el valor mágico",
    "Me conoces"};

char *questions[CANT_CHALLENGES] = {
    "¿Cómo descubrieron el protocolo, la dirección y el puerto para conectarse?",
    "¿Qué diferencias hay entre TCP y UDP y en qué casos conviene usar cada uno?",
    "¿El puerto que usaron para conectarse al server es el mismo que usan para mandar las respuestas? ¿Por qué?",
    "¿Qué útil abstracción es utilizada para comunicarse con sockets? ¿se puede utilizar read(2) y write(2) para operar?",
    "¿Cómo garantiza TCP que los paquetes llegan en orden y no se pierden?",
    "Un servidor suele crear un nuevo proceso o thread para atender las conexiones entrantes. ¿Qué conviene más?",
    "¿Cómo se puede implementar un servidor que atienda muchas conexiones sin usar procesos ni threads?",
    "¿Qué aplicaciones se pueden utilizar para ver el tráfico por la red?",
    "sockets es un mecanismo de IPC. ¿Qué es más eficiente entre sockets y pipes?",
    "¿Cuáles son las características del protocolo SCTP?",
    "¿Qué es un RFC?"};

char *answers[CANT_CHALLENGES] = {
    "entendido",
    "itba",
    "M4GFKZ289aku",
    "fk3wfLCm3QvS",
    "too_easy",
    ".RUN_ME",
    "K5n2UFfpFMUN",
    "BUmyYq5XxXGt",
    "u^v\cdot ln\left(u\right)\cdot v",
    "chin_chu_lan_cha",
    "gdb_rules",
    "normal"
    };

#endif