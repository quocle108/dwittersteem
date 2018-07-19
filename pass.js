const bcrypt = require('bcrypt');
var mongo = require('mongodb');
var ObjectId = require('mongodb').ObjectId;
var MongoClient = require('mongodb').MongoClient;
var url = process.env.MONGODB_URI;


function passAccount(){
	MongoClient.connect(url, function(err, db) {
					if (err){
				console.log(err);
				throw err;
			}
   		var dbo = db.db("heroku_dg3d93pq");
   		
   		dbo.collection("user").find().toArray(function(err, data){
			if (err){
				console.log(err);
				throw err;
			}
			console.log(data);
			console.log("res",data.length);
			for(j=0;j<data.length;j++)
				console.log(data[j]);
			
      			for(i = 0; i < data.length ; i++){
				let id = data[i].account;
				let pass = data[i].pass;
				console.log("before",id,pass);
        			bcrypt.hash(pass, process.env.SALT, function(err, hash){
          				var newValue = hash;
					var myobj = { $set: {pass : newValue}};
					var findquery = { account : id };
            				dbo.collection("user").updateOne(findquery, myobj, function(err,result){
						if (err){
							console.log(err);
							throw err;
						}else{
							console.log(id, pass, newValue);
						}

            				});
				});				
			}			
		});
	});          						
}

passAccount();


