import subprocess

def run_test(program_path, *args):
    command = ['./curiosity-perf', program_path, *map(str, args)]
    result = subprocess.run(command, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
    return result.stdout

def main():
    test_range = range(1, 8)  
    with open('stats2.txt', 'w') as stats_file:
        for test_number in test_range:
            program_path = f'./TestTP08/inf{test_number}.prg'
            output = run_test(program_path, 20, 9, 9, 0.7, 69, 1000, f'rzlt{test_number}')
            
            stats_file.write(f'Test {test_number}:\n{output}\n\n')
    print(f'OK B&B, Vos stats sont dans : stats.txt :))')

if __name__ == "__main__":
    main()
