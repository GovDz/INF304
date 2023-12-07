import subprocess
import glob

def run_curiosity_test(program_file, output_file):
    command = ["./../curiosity-test", program_file]
    with open(output_file, 'w') as out_file:
        subprocess.run(command, stdout=out_file, stderr=subprocess.STDOUT)

def main():
    # Find files matching the pattern "programme_test*"
    program_files = glob.glob("programme_test*")

    if not program_files:
        print("No matching files found.")
        return

    # Run the curiosity-test for each program file and write output to a file
    for program_file in program_files:
        output_file = f"{program_file}_output.txt"
        print(f"Running curiosity-test for {program_file}. Output will be saved in {output_file}")
        run_curiosity_test(program_file, output_file)

if __name__ == "__main__":
    main()
