import numpy as np

def main():
	file = open("mem_init.txt", "r")
	memory_data_total = file.read()
	memory_words = memory_data_total.split()
	mem_ints = [int(a) for a in memory_words]
	
	memory = np.array(mem_ints)
	
	mem_addr1 = memory[0:4096]
	mem_addr2 = memory[16384:16384+4096]

	diff = mem_addr2 - mem_addr1
	SAD_total = abs(diff)

	SAD_partitioned = np.zeros(64, dtype=int)

	for idx in range(64):
		SAD_partitioned[idx] = sum(SAD_total[idx*64 : (idx+1)*64])
		print(SAD_total[idx*64 : (idx+1)*64])

	print("sad_values = {", end="")
	for value in SAD_partitioned:
		print(value, end=",")
	print("}", end="\n")
	print(SAD_partitioned)
	print(sum(SAD_partitioned))



if __name__ == "__main__":
	main()
