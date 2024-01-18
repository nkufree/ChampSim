with open("test.log", "r", encoding="utf-8") as f:
    data = f.readlines()
info = {"i_prefetcher": "my", "prefetcher": "my", "replacement": "my"}
for row in data:
    if "CPU 0 cumulative IPC:" in row:
        res = row.split()
        print("IPC:", res[4])
        info["IPC"] = res[4]
    elif "cpu0_L1D TOTAL" in row:
        res = row.split()
        LLC_hit = int(res[5]) / int(res[3])
        print("cpu0_L1D hitrate:", LLC_hit)
        info["L1D"] = "{:.2f}".format(LLC_hit * 100)
    elif "cpu0_L1I TOTAL" in row:
        res = row.split()
        LLC_hit = int(res[5]) / int(res[3])
        print("cpu0_L1I hitrate:", LLC_hit)
        info["L1I"] = "{:.2f}".format(LLC_hit * 100)
    elif "cpu0_L2C TOTAL" in row:
        res = row.split()
        LLC_hit = int(res[5]) / int(res[3])
        print("cpu0_L2C hitrate:", LLC_hit)
        info["L2C"] = "{:.2f}".format(LLC_hit * 100)
    elif "LLC TOTAL" in row:
        res = row.split()
        LLC_hit = int(res[5]) / int(res[3])
        print("LLC hitrate:", LLC_hit)
        info["LLC"] = "{:.2f}".format(LLC_hit * 100)