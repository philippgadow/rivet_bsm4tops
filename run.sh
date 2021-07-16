mkdir -p run
cd run

# run rivet
athena ../jo/test.py

# make plots
# rivet-mkhtml --errs -o my_plots MyOutput.yoda.gz:"Title=MC 1" MyOutput.yoda.gz:"Title=MC 2"
rivet-mkhtml --errs -o my_plots MyOutput.yoda.gz:"Title=MC 1"
