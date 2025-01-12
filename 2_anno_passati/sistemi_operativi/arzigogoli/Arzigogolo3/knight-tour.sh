# Verifica che una posizione non sia fuori dalla scacchiera oppure non sia già stata visitata
is_valid_move() {
	local x=$1
	local y=$2
	[ $x -ge 0 ] && [ $x -lt $dim ] && [ $y -ge 0 ] && [ $y -lt $dim ] && [ ${visited[x+y*dim]} -eq -1 ]
}

# Conta le mosse possibili a partire da una cella della scacchiera
count_posible_moves() {
	local x=$1
	local y=$2
	count=0

	declare -i i=0
	while [ $i -lt 8 ]; do
		local new_x=$((x + ${moves[i]%% *}));
		local new_y=$((y + ${moves[i]##* }));
		if is_valid_move $new_x $new_y; then
			let count++;
		fi
		let i++;
	done
}

# Cerca la mossa giusta a partire dalla cella fornita (implementazione della regola di Warnsdorff)
find_move() {
	# Minime mosse possibili per una cella raggiungibile
	min_n_move=9;

	# Cicla su tutte le mosse (valide e non) a partire da una cella
	declare -i i=0;
	while [ $i -lt 8 ]; do
		local new_x=$((x + ${moves[i]%% *}));
		local new_y=$((y + ${moves[i]##* }));
		if is_valid_move $new_x $new_y; then
			# Conta quante sono le mosse possibili per tutte le mosse valide
			count_posible_moves $new_x $new_y
			# Se il numero di mosse possibili è più piccolo del precedente minimo, sostituisce la mossa
			if [ $count -lt $min_n_move ]; then
				min_n_move=$count;
				right_move=${moves[i]};
			fi
		fi
		let i++
	done
	local right_move_x=${right_move%% *}
	local right_move_y=${right_move##* }
	x=$((x + ${right_move_x:=0}));
	y=$((y + ${right_move_y:=0}));
}

# Funzione ricorsiva per calcolare la scacchiera con l'ordine delle mosse nelle celle
knight_tour() {
	local move=$1
	local x=$2
	local y=$3

	# Aggiorna l'array delle celle visitate
	visited[$((x + y*dim))]=1

	# Inserisce la casella occupata al passo corrispondente
	steps[$move]=$((x+y*dim))

	# Trova la prossima mossa
	find_move

	# Se la variabile min_n_move è uguale a 9, vuol dire che non sono state trovate mosse valide, termina la ricorsione
	if [ $min_n_move -ne 9 ]; then
		knight_tour $((move+1)) $x $y
	fi

	# Se il numero dell'ultima mossa è diverso dalla dimensione della scacchiera-1, il gioco non è stato risolto
	if [ $move -ne $((dim*dim-1)) ]; then
		echo "Non ho trovato una soluzione completa"
		echo
	fi

	# Stampa la sequenza delle caselle su cui passa il cavallo
	declare -i i=0
	while :; do
		printf "%s" ${steps[i]:-'-'}
		if [ $i -eq $((dim*dim-1)) ]; then
			echo
			break
		fi
		printf " "
		let i++;
	done

	exit 0
}

# Controlla che il numero di parametri sia corretto
if [ $# -ne 2 ]; then
    echo "Numero di parametri non valido"
    exit 1
fi

dim=$1
start=$2

# Controlla che la dimensione della scacchiera abbia senso
if [ $dim -lt 1 ]; then
	echo "La dimensione della scacchiera non può essere più piccola di 1x1"
	exit 2
fi

#Controlla che la posizione di partenza sia all'interno della scacchiera
if [ $start -lt 0 ] || [ $start -ge $((dim*dim)) ]; then
	echo "La posizione di partenza è fuori dalla scacchiera"
	exit 3
fi

# Calcola x e y iniziali
start_x=$((start%dim));
start_y=$((start/dim));

# Inizializzazione dell'array delle calle visitate
declare -i i=0
while [ $i -lt $((dim*dim)) ]; do
	visited[$i]="-1";
	let i++;
done

# Array con tutte le mosse possibili per un cavallo
moves=("2 1" "1 2" "-1 2" "-2 1" "-2 -1" "-1 -2" "1 -2" "2 -1" "0 0")

# Prima chiamata della funzione ricorsiva
knight_tour 0 $start_x $start_y
