import csv
import sys


def main():

    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        sys.exit(1)

    rows_dict = []  # This is a list

    # TODO: Read database file into a variable
    with open(sys.argv[1], "r") as database:
        dtb_reader1 = csv.DictReader(database)  # file as argument

        for row in dtb_reader1:
            rows_dict.append(row)

        labels = dtb_reader1.fieldnames

    # TODO: Read DNA sequence file into a variable
    with open(sys.argv[2], "r") as data_seq:
        ds_reader = data_seq.read()
        # print(ds_reader, end="")

    # TODO: Find longest match of each STR in DNA sequence
    STR_dict = {}
    for l in labels:
        if l == 'name':
            continue

        lm = longest_match(ds_reader, l)
        STR_dict[l] = lm

    # TODO: Check database for matching profiles
    match = False
    for element in rows_dict:
        for key, value in zip(STR_dict.keys(), STR_dict.values()):
            if int(element[key]) == value:
                match = True
            else:
                match = False
                break

        if match:
            print(element["name"])
            break

    print("No Match")
    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
