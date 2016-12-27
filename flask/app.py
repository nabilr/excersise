from flask import Flask, render_template, request, redirect, url_for
app = Flask(__name__)


@app.route('/submit',methods=['POST'])
def submit():

	#print(request.form)
	
	var1=request.form['nm']
	var2=request.form['nn']
	
	#reference
	#https://www.tutorialspoint.com/flask/flask_url_building.htm
	print(url_for('my_results',var1=var1,var2=var2))
	return redirect(url_for('my_results',var1=var1,var2=var2))


#Reference:
#https://www.tutorialspoint.com/flask/flask_variable_rules.htm
#Eg:
#http://127.0.0.1:5000/name/nabil
#here var1 is 'name' and 'var2' is nabil
@app.route('/<var1>/<var2>')
def my_results(var1, var2):
	print(var1, var2)

	#reference 
	#https://www.tutorialspoint.com/flask/flask_templates.htm
	#if you are using render_template function the file has to be inside template folder	
	return render_template('results.html', m1=var1,m2=var2)

if __name__ == '__main__':
   app.run(debug = True)
