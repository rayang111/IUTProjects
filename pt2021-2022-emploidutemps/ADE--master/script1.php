<?php
/*
 * API Web PHP permetant une connexion sécurisée. (POUR ADMINS)
 *
 * */

//var_dump($argv);

/*if(isset($_COOKIE['connected'])){
    echo "Connecté.\n";
} else{
    echo "Pas connecté.\n";
}*/

if(isset($_GET['VarGrpId'])){
    //echo "Caca \n";
    getWeekByGroupId($_GET['groupid']);
} else if(isset($_GET['Add'])){
    addCase($_GET['groupid'], $_GET['subject'], $_GET['date'], $_GET['hour'], $_GET['type']);
} else if(isset($_GET['VarSub'])){
    getWeekBySubject($_GET['subject']);
} else if(isset($_GET['VarDate'])){
    getWeekByDate($_GET['date']);
} else if(isset($_POST['Connect'])){
    try{
        _getConnection();
        if(getAccount($_POST['login'],$_POST['pwd']) === false){
            throw new Exception("Login ou mot de passe incorrect",);
        } else{
            echo "0";
        }
    } catch(Exception $e){
        echo "1";
        exit(1);
    }
} else if(isset($_POST['Create'])){
    if(setAccount($_POST['login'],$_POST['pwd'])){ //,$_POST['groupid']
        echo "Creation d'un compte";
    }
} else if(isset($_POST['Remouve'])){
    removeCase($_POST['id']);
} else if(isset($_POST['Edit'])){
    if(isset($_POST['EditGroupId'])){
        editCaseGroupId($_POST['id'],);
    } else if(isset($_POST['EditSubject'])){
        editCaseSubject($_POST['id'], $_POST['subject']);
    } else if(isset($_POST['EditDate'])){
        editCaseDate($_POST['id'], $_POST['date']);
    } else if(isset($_POST['EditHour'])){
        editCaseHour($_POST['id'], $_POST['hour']);
    } else if(isset($_POST['EditType'])){
        editCaseType($_POST['id'], $_POST['type']);
    }
} else if(isset($_POST['GetGroups'])){
    getGroups();    
}


function _getConnection()
{
	static $_conn = NULL;
	if ($_conn === NULL){
		$_conn = new PDO("mysql:host=dwarves.iut-fbleau.fr;charset=UTF8;dbname=grib","grib","grib");
	}
	return $_conn;
}

function setAccount($login, $pwd) //, $groupid
{
	$conn = _getConnection();
	try{
        $stmt = $conn ->prepare("INSERT INTO connect(login,pwd) VALUES(:login, :pwd);");
        $hashPwd = hash('sha256', filter_var($pwd, FILTER_SANITIZE_STRING));
        $stmt->bindValue(':login', filter_var($login, FILTER_SANITIZE_STRING), PDO::PARAM_STR);
        $stmt->bindValue(':pwd', $hashPwd, PDO::PARAM_STR);
        $stmt->execute();
        return true;
    } catch(Exception $e){
        echo 'Exception reçue : ',  $e->getMessage(), "\n";
    }

}

function getAccount($login, $pwd)
{
	$conn = _getConnection();
	try{
        $stmt = $conn ->prepare("SELECT login, pwd FROM connect WHERE login = :login AND pwd = :pwd;");
        $hashPwd = hash('sha256', filter_var($pwd, FILTER_SANITIZE_STRING));
        $stmt->bindValue(':login', filter_var($login, FILTER_SANITIZE_STRING), PDO::PARAM_STR);
        $stmt->bindValue(':pwd', $hashPwd, PDO::PARAM_STR);
        $stmt->execute();
        $connected = false;
        foreach($stmt as $element){
            if($element[0] === $login && $element[1] === $hashPwd){
                //echo "Connection en cours";
                $connected = true;
                setcookie('connected',$connected,mktime(12,34,00,04,01,2030));
                return true;
            }
        }
        if($connected === false){
            return false;
        }
    }
    catch(Exception $e){
        echo 'Exception reçue : ',  $e->getMessage(), "\n";
        return false;
    }

}

function getGroups(){
    $conn = _getConnection();
    try{
        $stmt = $conn ->prepare("SELECT groupid, name FROM groups;");
        $stmt->execute();
        $res = array("groups" => array());
       foreach($stmt as $element){
            array_push($res["groups"], $element);
       }
       echo json_encode($res);
    } catch(Exception $e){
         echo 'Exception reçue : ',  $e->getMessage(), "\n";
    }
}

function getWeekByGroupId($groupid)
{
    $conn = _getConnection();
    try{
        $stmt = $conn ->prepare("SELECT id, groupid, subject, date, hour, type FROM adeCase WHERE groupid = :groupid;");
        $stmt->bindValue(':groupid', filter_var($groupid, FILTER_SANITIZE_STRING), PDO::PARAM_STR);
        $stmt->execute();
        $res = array("edt" => array());
        foreach($stmt as $element){
            array_push($res["edt"], $element);
        }
        echo json_encode($res);
    }
    catch(Exception $e){
        echo 'Exception reçue : ',  $e->getMessage(), "\n";
    }
}

function getWeekBySubject($subject)
{
    $conn = _getConnection();
    try{
        $stmt = $conn ->prepare("SELECT id, groupid, subject, date, hour, type FROM adeCase WHERE subject = :subject;");
        $stmt->bindValue(':subject', filter_var($subject, FILTER_SANITIZE_STRING), PDO::PARAM_STR);
        $stmt->execute();
        $res = array("edt" => array());
        foreach($stmt as $element){
            array_push($res["edt"], $element);
        }
        echo json_encode($res);
    }
    catch(Exception $e){
        echo 'Exception reçue : ',  $e->getMessage(), "\n";
    }
}

function getWeekByDate($date)
{
    $conn = _getConnection();
    try{
        $stmt = $conn ->prepare("SELECT id, groupid, subject, date, hour, type FROM adeCase WHERE date = :date;");
        $stmt->bindValue(':date', filter_var($date, FILTER_SANITIZE_STRING), PDO::PARAM_STR);
        $stmt->execute();
        $res = array("edt" => array());
        foreach($stmt as $element){
            array_push($res["edt"], $element);
        }
        echo json_encode($res);
    }
    catch(Exception $e){
        echo 'Exception reçue : ',  $e->getMessage(), "\n";
    }
}

function addCase($groupid, $subject, $date, $hour, $type)
{
    $conn = _getConnection();
    try{
        $stmt = $conn ->prepare("INSERT INTO adeCase(groupid, subject, date, hour, type) VALUES(:groupid, :subject, :date, :hour, :type);");
        $stmt->bindValue(':groupid', $groupid, PDO::PARAM_STR);
        $stmt->bindValue(':subject', $subject, PDO::PARAM_STR);
        $stmt->bindValue(':date', $date, PDO::PARAM_STR);
        $stmt->bindValue(':hour', $hour, PDO::PARAM_STR);
        $stmt->bindValue(':type', $type, PDO::PARAM_STR);
        $stmt->execute();

    }
    catch(Exception $e){
        echo 'Exception reçue : ',  $e->getMessage(), "\n";
    }
}

function editCaseGroupId($id, $groupid){
     $conn = _getConnection();
     try{
         $stmt = $conn ->prepare("UPDATE addCase SET groupid = :groupid WHERE id = :id;");
         $stmt->bindValue(':groupid', $groupid, PDO::PARAM_STR);
         $stmt->bindValue(':id', $id, PDO::PARAM_STR);
         $stmt->execute();
     }
     catch(Exception $e){
        echo 'Exception reçue : ',  $e->getMessage(), "\n";
    }
}

function editCaseSubject($id, $subject){
     $conn = _getConnection();
     try{
         $stmt = $conn ->prepare("UPDATE addCase SET subject = :subject WHERE id = :id;");
         $stmt->bindValue(':subject', $subject, PDO::PARAM_STR);
         $stmt->bindValue(':id', $id, PDO::PARAM_STR);
         $stmt->execute();
     }
     catch(Exception $e){
        echo 'Exception reçue : ',  $e->getMessage(), "\n";
    }
}

function editCaseDate($id, $date){
     $conn = _getConnection();
     try{
         $stmt = $conn ->prepare("UPDATE addCase SET date = :date WHERE id = :id;");
         $stmt->bindValue(':date', $date, PDO::PARAM_STR);
         $stmt->bindValue(':id', $id, PDO::PARAM_STR);
         $stmt->execute();
     }
     catch(Exception $e){
        echo 'Exception reçue : ',  $e->getMessage(), "\n";
    }
}

function editCaseHour($id, $groupid){
     $conn = _getConnection();
     try{
         $stmt = $conn ->prepare("UPDATE addCase SET hour = :hour WHERE id = :id;");
         $stmt->bindValue(':hour', $hour, PDO::PARAM_STR);
         $stmt->bindValue(':id', $id, PDO::PARAM_STR);
         $stmt->execute();
     }
     catch(Exception $e){
        echo 'Exception reçue : ',  $e->getMessage(), "\n";
    }
}

function editCasType($id, $type){
     $conn = _getConnection();
     try{
         $stmt = $conn ->prepare("UPDATE addCase SET type = :type WHERE id = :id;");
         $stmt->bindValue(':type', $type, PDO::PARAM_STR);
         $stmt->bindValue(':id', $id, PDO::PARAM_STR);
         $stmt->execute();
     }
     catch(Exception $e){
        echo 'Exception reçue : ',  $e->getMessage(), "\n";
    }
}

function removeCase($id)
{
    $conn = _getConnection();
    try{
        $stmt = $conn ->prepare("DELETE FROM adeCase WHERE id = :id;");
        $stmt->bindValue(':id', $id, PDO::PARAM_STR);
        $stmt->execute();
    }
    catch(Exception $e){
        echo 'Exception reçue : ',  $e->getMessage(), "\n";
    }
}

function _closeConnection($conn)
{
    if($conn !== NULL){
        setcookie("connected","",1);
		exit();
    }
}

_closeConnection(_getConnection());
?>