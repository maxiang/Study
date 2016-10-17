// 初始化
mui.init();

var main = null;
var showMenu = false;
var menu = null;

// 所有方法都放到这里
mui.plusReady(function(){
	// 初始化数据库
	initialize()
	// 侧滑菜单
	main = plus.webview.getWebviewById(plus.runtime.appid);
	var menuoptions = {
		url: 'views/menu.html',
		id: 'menu',
		styles : {
			left:0,
			width:'70%',
			zindex:-1
		}
	};
	menu = mui.preload(menuoptions);
//	$(document).off('tap', '.btnMenu').on('tap', '.btnAdd', opMenu);
	mui('.mui-bar').on('tap', '.btnMenu', opMenu);
	main.addEventListener('maskClick', opMenu);
	mui.menu = opMenu;

	// 退出
	mui.back = function(){
//		if($('.adda').is(':hidden')){
//			hideAdd();	
//		}else if(showMenu){
//			closeMenu();
//		}else{
//			qiao.h.exit();
//		}
	};
	
});

// menu
function opMenu(){
	console.log("showMenu: ", showMenu);
	if(showMenu){
		closeMenu();
	}else{
		openMenu();
	}
}
function openMenu(){
//	if($('.adda').is(':visible')){
//		setColor("#333333");
		menu.show('none', 0, function() {
			main.setStyle({
				mask: 'rgba(0,0,0,0.4)',
				left: '70%',
				transition: {
					duration: 150
				}
			});
	
			showMenu = true;
		});
//	}
}
function closeMenu(){
//	setColor("#f7f7f7");
	main.setStyle({
		mask: 'none',
		left: '0',
		transition: {
			duration: 100
		}
	});
	
	showMenu = false;
	setTimeout(function() {
		menu.hide();
	}, 300);
}

// set color
//function setColor(color){
//	if(mui.os.ios && color) plus.navigator.setStatusBarBackground(color);
//}

mui('body').on('shown', '.mui-popover', function(e) {
	console.log('shown', e.detail.id);//detail为当前popover元素
});
mui('body').on('hidden', '.mui-popover', function(e) {
	console.log('hidden', e.detail.id);//detail为当前popover元素
});
	
function newaddEvent(){
	var text = document.getElementById("textarea");
	if(!text.value||text.value==""){
				mui.toast("不允许为空");
				return false;
	}
	console.log(text);	
}

function getDatabase() {
     return openDatabase("testdb", "1.0", "page", 123456);
}

function initialize(){
    var db = getDatabase()
    db.transaction(function(tx){
    	tx.executeSql("CREATE TABLE IF NOT EXISTS testTable (name TEXT, value TEXT, primary key (name))");
    });
    
    console.log("initialize ... ");
    
    var ret = addValue("c10", "10");
    console.log(ret);
    
    loadValue();
}

function addValue(cname, cvalue){
    var db = getDatabase();
    var res = true;
    db.transaction(function(tx){
        tx.executeSql('INSERT INTO testTable VALUES (?,?);',[cname, cvalue],
	        function(tx,results){
				console.log(cname);
	        },function (tx, error){
	            res = false;
	            console.log("addValue error.");
	        }
        );
    })

    return res;
}

function loadValue(){
	console.log("loadValue ... ");
    var db = getDatabase();
    db.transaction(function(tx){
    	tx.executeSql('SELECT * FROM testTable', [], 
    	function (tx, results) {
    		var htmlList = new Array();
		    var len = results.rows.length;
		    for (i = 0; i < len; i++){
//		    	htmlList[i] = results.rows.item(i).ctitle;
				console.log(results.rows.item(i).name);
		    }
		},
    	function (tx,error){
    	  	console.log("loadValue error.");
    	});
		
	})
}