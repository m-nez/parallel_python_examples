import threading

def busy_loop():
    while True:
        pass

if __name__ == "__main__":

    num_threads = 2
    threads = []

    for i in range(num_threads):
        t = threading.Thread(target=busy_loop)
        t.start()
        threads.append(t)

    for t in threads:
        t.join()
