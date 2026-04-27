class FSM:
    def __init__(self):
        self.transitions = {
            'S': {'0': 'A', '1': 'B'},
            'A': {'0': 'C', '1': 'B'},
            'B': {'0': 'A', '1': 'B'},
            'C': {'0': 'C', '1': 'C'}
        }
        self.start_state = 'S'
        self.accept_states = {'B'}

    def process_string(self, input_string):
        current_state = self.start_state
        path = [current_state]

        for char in input_string:
            if char not in ['0', '1']:
                return False, path, "Karakter tidak valid (hanya 0 dan 1)"
            
            # Transisi ke state berikutnya berdasarkan input
            current_state = self.transitions[current_state][char]
            path.append(current_state)

        is_accepted = current_state in self.accept_states
        return is_accepted, path, "Selesai"

def main():
    print("FSM: String berakhiran 1 & tanpa '00'")
    
    fsm = FSM()
    
    while True:
        user_input = input("Masukkan string biner (0/1): ").strip()
        
        if user_input.lower() in ['exit', 'quit']:
            print("Program dihentikan.")
            break
            
        if not user_input:
            print("[!] String tidak boleh kosong.\n")
            continue
            
        accepted, path, msg = fsm.process_string(user_input)
        
        print(f"Jalur Transisi : {' -> '.join(path)}")
        if msg != "Selesai":
            print(f"Status         : REJECTED ({msg})\n")
        elif accepted:
            print(f"Status         : ACCEPTED (Berakhir di state {path[-1]})\n")
        else:
            print(f"Status         : REJECTED (Berakhir di state {path[-1]}, bukan final state)\n")

if __name__ == "__main__":
    main()
