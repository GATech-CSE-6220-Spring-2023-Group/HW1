# HW1

CSE-6220 HW1

## Make and run

Run the following to make and run the program `int_calc` with $n=2000$ and $p=4$:

```shell
$ make run n=2000 p=8
```

By default, `n = 1000, p=4`.

## Create report charts

Note: Must have `matplotlib` package installed to create report charts.

Example: Create a report chart with n=1M, comparing p=[1,10], and save it to the file `report_chart.jpg`:

```shell
$ python report_chart.py -p=10 -n 1000000 -o report_chart_n_1M.jpg
```

![](report_chart_n_1M.jpg)

Example: Same as above, but with n=1B:

```shell
$ python report_chart.py -p=10 -n 1000000000 -o report_chart_n_1B.jpg
```

![](report_chart_n_1B.jpg)
