import subprocess
import glob

def run_curiosity_test(program_file, output_file):
    command = ["./../curiosity-test", program_file]
    with open(output_file, 'a') as out_file:
        subprocess.run(command, stdout=out_file, stderr=subprocess.STDOUT)

def main():
    # Find files matching the pattern "programme_test*"
    program_files = glob.glob("programme_test*")

    if not program_files:
        print("No matching files found.")
        return

    # Open a single output file for all tests
    output_filename = "output.txt"
    with open(output_filename, 'w') as overall_output_file:
        # Run the curiosity-test for each program file and append output to the overall output file
        for program_file in program_files:
            output_file = f"{program_file}_output.txt"
            print(f"Running curiosity-test for {program_file}. Output will be saved in {output_file}")
            run_curiosity_test(program_file, output_file)

            # Read the output of the specific test and append it to the overall output file
            with open(output_file, 'r') as specific_output_file:
                overall_output_file.write(f"\n\n=== Output for {program_file} ===\n\n")
                overall_output_file.write(specific_output_file.read())

if __name__ == "__main__":
    main()
