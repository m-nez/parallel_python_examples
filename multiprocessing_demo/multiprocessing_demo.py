import multiprocessing

def busy_loop():
    while True:
        pass

if __name__ == "__main__":

    num_processes = 2
    processes = []

    for i in range(num_processes):
        p = multiprocessing.Process(target=busy_loop)
        p.start()
        processes.append(p)

    for p in processes:
        p.join()
