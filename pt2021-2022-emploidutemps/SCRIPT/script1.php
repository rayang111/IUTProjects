<?php
/*
 * API Web PHP permetant une connexion sécurisée. (POUR ADMINS)
 *
 * */

/*conection*/
if(isset($_POST['Connect'])){
    try{
        _getConnection();
        if(getAccount($_POST['login'],$_POST['pwd']) === false){
            throw new Exception("Login ou mot de passe incorrect");
        } 
    } catch(Exception $e){
        echo "1";
        exit(1);
    }
} 

/*add element*/
if(isset($_GET['Add'])){
    addCase($_GET['groupid'], $_GET['subject'], $_GET['date'], $_GET['hourdebut'],$_GET['hourfin'],$_GET['mindebut'],$_GET['minutefin'], $_GET['type'], $_GET['idprof'], $_GET['idlieu']);
}

if(isset($_POST['Create'])){
    setAccount($_POST['login'],$_POST['pwd']);   
} 

if(isset($_POST['addprof'])){
    setenseignant($_POST['idadmin'],$_POST['nom'],$_POST['login'],$_POST['pwd']);
}

if(isset($_POST['addsalle'])){
 setsalle($_POST['idadmin'],$_POST['nom']); 
}

if(isset($_POST['addgroupe'])){
  addGroup($_POST['idadmin'],$_POST['name'],$_POST['login'],$_POST['pwd']); 
}

/*remove element*/
if(isset($_POST['Remouve'])){
    removeCase($_POST['id']);
}

if(isset($_POST['removeprof'])){
    removeProf($_POST['id']);
}

if(isset($_POST['removesalle'])){
 removeSalle($_POST['id']); 
}

if(isset($_POST['removegroupe'])){
  removeGroup($_POST['id']); 
}

/*edit element*/
if(isset($_POST['editprof'])){
    editProf($_POST['id'],$_POST['nom'],$_POST['login'],$_POST['pwd']); 
}

if(isset($_POST['editsalle'])){
    editSalle($_POST['id'],$_POST['nom']); 
}

if(isset($_POST['editgroupe'])){
    editGroup($_POST['id'],$_POST['name'],$_POST['login'],$_POST['pwd']);
}

if(isset($_POST['editcase'])){
    editCase($_POST['id'],$_POST['groupid'], $_POST['subject'], $_POST['date'], $_POST['hourdebut'],$_POST['hourfin'],$_POST['mindebut'],$_POST['minutefin'], $_POST['type'], $_POST['idprof'], $_POST['idlieu']);
}

/*getteur*/
if(isset($_GET['VarGrpId'])){
    getWeekByGroupId($_GET['groupid'],$_GET['date'],$_GET['type']);
}

if(isset($_GET['VarProfId'])){
    getWeekByGroupIdprof($_GET['id'],$_GET['date']);
}

if(isset($_GET['getprof'])){
    getenseignant($_GET['idadmin']);
}

if(isset($_GET['getsalle'])){
    getsalle($_GET['idadmin']);
}

if(isset($_GET['getgroupe'])){
    getGroups($_GET['idadmin']);
}

/*-----------------------connection-----------------------*/
//fait la connection
function _getConnection()
{
	static $_conn = NULL;
	if ($_conn === NULL){
		$_conn = new PDO("mysql:host=dwarves.iut-fbleau.fr;charset=UTF8;dbname=grib","grib","PTKC");
	}
	return $_conn;
}

//close la connection
function _closeConnection($conn)
{
    if($conn !== NULL){
        setcookie("connected","",1);
        exit();
    }
}

/*----------------------- add element -----------------------*/
//creer un compte admin
function setAccount($login, $pwd) 
{
    $conn = _getConnection();
    try{
        $stmt = $conn ->prepare("SELECT count(*) FROM connect NATURAL JOIN groups NATURAL JOIN enseignant WHERE login = :login AND pwd = :pwd");
        $hashPwd = hash('sha256', filter_var($pwd, FILTER_SANITIZE_STRING));
        $stmt->bindValue(':login', filter_var($login, FILTER_SANITIZE_STRING), PDO::PARAM_STR);
        $stmt->bindValue(':pwd', $hashPwd, PDO::PARAM_STR);
        $stmt->execute();
        foreach($stmt as $element)
        {
            $res=$element[0];
        }
        $flag=1;
        if($res!='0')
        {
            echo 'false';
            $flag=0;
        }

        if($flag!=0)
        {
            $stmt = $conn ->prepare("INSERT INTO connect(login,pwd) VALUES(:login, :pwd);");
            $hashPwd = hash('sha256', filter_var($pwd, FILTER_SANITIZE_STRING));
            $stmt->bindValue(':login', filter_var($login, FILTER_SANITIZE_STRING), PDO::PARAM_STR);
            $stmt->bindValue(':pwd', $hashPwd, PDO::PARAM_STR);
            $stmt->execute();
            echo 'true';
            return true;
        }

        
    } catch(Exception $e){
        echo 'Exception reçue : ',  $e->getMessage(), "\n";
    }

}

//creer un intervenant
function setenseignant($idadmin,$nom,$login,$pwd)
{
    $conn = _getConnection();
    try{
        $stmt = $conn ->prepare("INSERT INTO enseignant(idadmin,nom,login,pwd) VALUES(:idadmin,:nom,:login,:pwd);");
        $hashPwd = hash('sha256', filter_var($pwd, FILTER_SANITIZE_STRING));
        $stmt->bindValue(':idadmin', filter_var($idadmin, FILTER_SANITIZE_STRING), PDO::PARAM_STR);
        $stmt->bindValue(':nom', filter_var($nom, FILTER_SANITIZE_STRING), PDO::PARAM_STR);
        $stmt->bindValue(':login', filter_var($login, FILTER_SANITIZE_STRING), PDO::PARAM_STR);
        $stmt->bindValue(':pwd', $hashPwd, PDO::PARAM_STR);
        $stmt->execute();
        return true;
    } catch(Exception $e){
        echo 'Exception reçue : ',  $e->getMessage(), "\n";
    }
}

//creer un salle
function setsalle($idadmin,$nom)
{
    $conn = _getConnection();
    try{
        $stmt = $conn ->prepare("INSERT INTO salle(idadmin,nom) VALUES(:idadmin,:nom);");
        $stmt->bindValue(':idadmin', filter_var($idadmin, FILTER_SANITIZE_STRING), PDO::PARAM_STR);
        $stmt->bindValue(':nom', filter_var($nom, FILTER_SANITIZE_STRING), PDO::PARAM_STR);
        $stmt->execute();
        return true;
    } catch(Exception $e){
        echo 'Exception reçue : ',  $e->getMessage(), "\n";
    }
}

//creer un groupe
function addGroup($idadmin,$name,$login,$pwd)
{
    $conn = _getConnection();
    try{
        $stmt = $conn ->prepare("INSERT INTO groups(name,login,pwd,idadmin) VALUES(:name,:login, :pwd, :idadmin);");
        $hashPwd = hash('sha256', filter_var($pwd, FILTER_SANITIZE_STRING));
        $stmt->bindValue(':login', filter_var($login, FILTER_SANITIZE_STRING), PDO::PARAM_STR);
        $stmt->bindValue(':name', filter_var($name, FILTER_SANITIZE_STRING), PDO::PARAM_STR);
        $stmt->bindValue(':idadmin', filter_var($idadmin, FILTER_SANITIZE_STRING), PDO::PARAM_STR);
        $stmt->bindValue(':pwd', $hashPwd, PDO::PARAM_STR);
        $stmt->execute();

        return true;
    } catch(Exception $e){
        echo 'Exception reçue : ',  $e->getMessage(), "\n";
    }
}

//ajoute un évenement
function addCase($groupid, $subject, $date, $hourdebut, $hourfin,$mindebut,$minutefin, $type, $idprof, $idlieu)
{
    $conn = _getConnection();
    $mindeb=(($hourdebut*60)+$mindebut);
    $minfin=(($hourfin*60)+$minutefin);
    $possible='0';
    if($hourdebut<=$hourfin){
     try{
        $flag=0;
        $stmt = $conn ->prepare("SELECT count(*) FROM adeCase WHERE (:date = date AND :idlieu=idlieu) AND ((:mindeb BETWEEN ((hour*60)+mindebut) AND ((hourfin*60)+minutefin)) OR (:minfin BETWEEN ((hour*60)+mindebut) AND ((hourfin*60)+minutefin)) OR (:mindeb < ((hour*60)+mindebut) AND :minfin > ((hourfin*60)+minutefin)))");


        $stmt->bindValue(':date', filter_var($date, FILTER_SANITIZE_STRING), PDO::PARAM_STR);
        $stmt->bindValue(':mindeb', filter_var($mindeb, FILTER_SANITIZE_STRING), PDO::PARAM_STR);
        $stmt->bindValue(':minfin', filter_var($minfin, FILTER_SANITIZE_STRING), PDO::PARAM_STR);
        $stmt->bindValue(':idlieu', filter_var($idlieu, FILTER_SANITIZE_STRING), PDO::PARAM_STR);
        $stmt->execute();

        foreach($stmt as $element)
        {
            $possible=$element[0];
        }

        if($possible!='0')
        {
            echo 'lieu';
            $flag=1;
        }

        $stmt = $conn ->prepare("SELECT count(*) FROM adeCase WHERE (:date = date AND :idprof=idintervenant) AND ((:mindeb BETWEEN ((hour*60)+mindebut) AND ((hourfin*60)+minutefin)) OR (:minfin BETWEEN ((hour*60)+mindebut) AND ((hourfin*60)+minutefin)) OR (:mindeb < ((hour*60)+mindebut) AND :minfin > ((hourfin*60)+minutefin)))");

        $stmt->bindValue(':date', filter_var($date, FILTER_SANITIZE_STRING), PDO::PARAM_STR);
        $stmt->bindValue(':mindeb', filter_var($mindeb, FILTER_SANITIZE_STRING), PDO::PARAM_STR);
        $stmt->bindValue(':minfin', filter_var($minfin, FILTER_SANITIZE_STRING), PDO::PARAM_STR);
        $stmt->bindValue(':idprof', filter_var($idprof, FILTER_SANITIZE_STRING), PDO::PARAM_STR);
        $stmt->execute();
        foreach($stmt as $element)
        {
            $possible=$element[0];
        }
        if($possible!='0' && $flag!=1)
        {
            echo 'prof';
            $flag=1;
        }

        $stmt = $conn ->prepare("SELECT count(*) FROM adeCase WHERE (:date = date AND :groupid=groupid) AND ((:mindeb BETWEEN ((hour*60)+mindebut) AND ((hourfin*60)+minutefin)) OR (:minfin BETWEEN ((hour*60)+mindebut) AND ((hourfin*60)+minutefin)) OR (:mindeb < ((hour*60)+mindebut) AND :minfin > ((hourfin*60)+minutefin)))");

        $stmt->bindValue(':groupid', filter_var($groupid, FILTER_SANITIZE_STRING), PDO::PARAM_STR);
        $stmt->bindValue(':date', filter_var($date, FILTER_SANITIZE_STRING), PDO::PARAM_STR);
        $stmt->bindValue(':mindeb', filter_var($mindeb, FILTER_SANITIZE_STRING), PDO::PARAM_STR);
        $stmt->bindValue(':minfin', filter_var($minfin, FILTER_SANITIZE_STRING), PDO::PARAM_STR);
        $stmt->execute();
        foreach($stmt as $element)
        {
            $possible=$element[0];
        }
        if($possible!='0' && $flag!=1)
        {
            echo 'group';
            $flag=1;
        }

        if($flag!=1) 
        {
            $stmt = $conn ->prepare("INSERT INTO adeCase(groupid, idintervenant, idlieu, subject, date, hour, mindebut, hourfin, minutefin, type) VALUES(:groupid, :idprof, :idlieu, :subject, :date, :hourdebut,:mindebut,:hourfin,:minutefin, :type);");
            $stmt->bindValue(':groupid', filter_var($groupid, FILTER_SANITIZE_STRING), PDO::PARAM_STR);
            $stmt->bindValue(':idprof', filter_var($idprof, FILTER_SANITIZE_STRING), PDO::PARAM_STR);
            $stmt->bindValue(':idlieu', filter_var($idlieu, FILTER_SANITIZE_STRING), PDO::PARAM_STR);
            $stmt->bindValue(':subject', filter_var($subject, FILTER_SANITIZE_STRING), PDO::PARAM_STR);
            $stmt->bindValue(':date', filter_var($date, FILTER_SANITIZE_STRING), PDO::PARAM_STR);
            $stmt->bindValue(':hourdebut', filter_var($hourdebut, FILTER_SANITIZE_STRING), PDO::PARAM_STR);
            $stmt->bindValue(':hourfin', filter_var($hourfin, FILTER_SANITIZE_STRING), PDO::PARAM_STR);
            $stmt->bindValue(':mindebut', filter_var($mindebut, FILTER_SANITIZE_STRING), PDO::PARAM_STR);
            $stmt->bindValue(':minutefin', filter_var($minutefin, FILTER_SANITIZE_STRING), PDO::PARAM_STR);
            $stmt->bindValue(':type', filter_var($type, FILTER_SANITIZE_STRING), PDO::PARAM_STR);
            $stmt->execute();
            echo'true'; 
        }


    }catch(Exception $e){
        echo 'Exception reçue : ',  $e->getMessage(), "\n";
    } 
}else{
    echo 'hour';
}
}



/*----------------------- remove element -----------------------*/

//suprime un groupe
function removeProf($id)
{
    $conn = _getConnection();
    try{
        $stmt = $conn ->prepare("DELETE FROM enseignant WHERE id=:id;");
        $stmt->bindValue(':id', filter_var($id, FILTER_SANITIZE_STRING), PDO::PARAM_STR);
        $stmt->execute();

        return true;
    } catch(Exception $e){
        echo 'Exception reçue : ',  $e->getMessage(), "\n";
    }
}

//suprime un intervenant
function removeGroup($id)
{
    $conn = _getConnection();
    try{
        $stmt = $conn ->prepare("DELETE FROM groups WHERE groupid=:id;");
        $stmt->bindValue(':id', filter_var($id, FILTER_SANITIZE_STRING), PDO::PARAM_STR);
        $stmt->execute();

        return true;
    } catch(Exception $e){
        echo 'Exception reçue : ',  $e->getMessage(), "\n";
    }
}

//suprime un lieu
function removeSalle($id)
{
    $conn = _getConnection();
    try{
        $stmt = $conn ->prepare("DELETE FROM salle WHERE id=:id;");
        $stmt->bindValue(':id', filter_var($id, FILTER_SANITIZE_STRING), PDO::PARAM_STR);
        $stmt->execute();

        return true;
    } catch(Exception $e){
        echo 'Exception reçue : ',  $e->getMessage(), "\n";
    }
}

//suprime un evenement
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


/*----------------------- edit element -----------------------*/

//modifie un groupe
function editGroup($id,$name,$login,$pwd)
{
  $conn = _getConnection();
  try{
    $stmt = $conn ->prepare("UPDATE groups SET name=:name, login=:login, pwd=:pwd WHERE groupid=:id;");
    $hashPwd = hash('sha256', filter_var($pwd, FILTER_SANITIZE_STRING));
    $stmt->bindValue(':id', filter_var($id, FILTER_SANITIZE_STRING), PDO::PARAM_STR);
    $stmt->bindValue(':name', filter_var($name, FILTER_SANITIZE_STRING), PDO::PARAM_STR);
    $stmt->bindValue(':login', filter_var($login, FILTER_SANITIZE_STRING), PDO::PARAM_STR);
    $stmt->bindValue(':pwd', $hashPwd, PDO::PARAM_STR);
    $stmt->execute();  

    return true;
} catch(Exception $e){
    echo 'Exception reçue : ',  $e->getMessage(), "\n";
}  
}

//modifie un intervenant
function editProf($id,$nom,$login,$pwd)
{


    $conn = _getConnection();
    try{
        $stmt = $conn ->prepare("UPDATE enseignant SET nom=:nom, login=:login, pwd=:pwd WHERE id=:id;");
        $hashPwd = hash('sha256', filter_var($pwd, FILTER_SANITIZE_STRING));
        $stmt->bindValue(':id', filter_var($id, FILTER_SANITIZE_STRING), PDO::PARAM_STR);
        $stmt->bindValue(':nom', filter_var($nom, FILTER_SANITIZE_STRING), PDO::PARAM_STR);
        $stmt->bindValue(':login', filter_var($login, FILTER_SANITIZE_STRING), PDO::PARAM_STR);
        $stmt->bindValue(':pwd', $hashPwd, PDO::PARAM_STR);
        $stmt->execute();  

        return true;
    } catch(Exception $e){
        echo 'Exception reçue : ',  $e->getMessage(), "\n";
    } 
}

//modifie un lieu
function editSalle($id,$nom)
{
    $conn = _getConnection();
    try{
        $stmt = $conn ->prepare("UPDATE salle SET nom=:nom WHERE id=:id;");
        $stmt->bindValue(':id', filter_var($id, FILTER_SANITIZE_STRING), PDO::PARAM_STR);
        $stmt->bindValue(':nom', filter_var($nom, FILTER_SANITIZE_STRING), PDO::PARAM_STR);
        $stmt->execute();

        return true;
    } catch(Exception $e){
        echo 'Exception reçue : ',  $e->getMessage(), "\n";
    }
}

//modifie l'evenement
function editCase($id, $groupid, $subject, $date, $hourdebut, $hourfin,$mindebut,$minutefin, $type, $idprof, $idlieu)
{
    $conn = _getConnection();
    try{
        $stmt = $conn ->prepare("UPDATE adeCase SET groupid=:groupid, idintervenant=:idprof, idlieu=:idlieu, subject=:subject, date=:date, hour=:hourdebut, mindebut=:mindebut, hourfin=:hourfin, minutefin=:minutefin, type=:type WHERE id=:id;");
            $stmt->bindValue(':id', filter_var($id, FILTER_SANITIZE_STRING), PDO::PARAM_STR);
            $stmt->bindValue(':groupid', filter_var($groupid, FILTER_SANITIZE_STRING), PDO::PARAM_STR);
            $stmt->bindValue(':idprof', filter_var($idprof, FILTER_SANITIZE_STRING), PDO::PARAM_STR);
            $stmt->bindValue(':idlieu', filter_var($idlieu, FILTER_SANITIZE_STRING), PDO::PARAM_STR);
            $stmt->bindValue(':subject', filter_var($subject, FILTER_SANITIZE_STRING), PDO::PARAM_STR);
            $stmt->bindValue(':date', filter_var($date, FILTER_SANITIZE_STRING), PDO::PARAM_STR);
            $stmt->bindValue(':hourdebut', filter_var($hourdebut, FILTER_SANITIZE_STRING), PDO::PARAM_STR);
            $stmt->bindValue(':hourfin', filter_var($hourfin, FILTER_SANITIZE_STRING), PDO::PARAM_STR);
            $stmt->bindValue(':mindebut', filter_var($mindebut, FILTER_SANITIZE_STRING), PDO::PARAM_STR);
            $stmt->bindValue(':minutefin', filter_var($minutefin, FILTER_SANITIZE_STRING), PDO::PARAM_STR);
            $stmt->bindValue(':type', filter_var($type, FILTER_SANITIZE_STRING), PDO::PARAM_STR);
            $stmt->execute();
            echo'true';

        return true;
    } catch(Exception $e){
        echo 'Exception reçue : ',  $e->getMessage(), "\n";
    }
}



/*----------------------- getteur -----------------------*/
//recupere un compte
function getAccount($login, $pwd)
{
    $conn = _getConnection();
    try{
        $stmt = $conn ->prepare("SELECT login, pwd, id FROM connect WHERE login = :login AND pwd = :pwd;");
        $hashPwd = hash('sha256', filter_var($pwd, FILTER_SANITIZE_STRING));
        $stmt->bindValue(':login', filter_var($login, FILTER_SANITIZE_STRING), PDO::PARAM_STR);
        $stmt->bindValue(':pwd', $hashPwd, PDO::PARAM_STR);
        $stmt->execute();
        $connected = false;
        $res = array("id" => array());
        foreach($stmt as $element){
            if($element[0] === $login && $element[1] === $hashPwd){
                array_push($res["id"], 'admin');
                array_push($res["id"], $element[2]);
                $connected = true;
                setcookie('connected',$connected,mktime(12,34,00,04,01,2030));
                echo json_encode($res);
            }
        }

        $stmt = $conn ->prepare("SELECT login, pwd, id FROM enseignant WHERE login = :login AND pwd = :pwd;");
        $hashPwd = hash('sha256', filter_var($pwd, FILTER_SANITIZE_STRING));
        $stmt->bindValue(':login', filter_var($login, FILTER_SANITIZE_STRING), PDO::PARAM_STR);
        $stmt->bindValue(':pwd', $hashPwd, PDO::PARAM_STR);
        $stmt->execute();
        $rep = array("id" => array());
        foreach($stmt as $element){
            if($element[0] === $login && $element[1] === $hashPwd){
                array_push($rep["id"], 'enseignant');
                array_push($rep["id"], $element[2]);
                $connected = true;
                setcookie('connected',$connected,mktime(12,34,00,04,01,2030));
                echo json_encode($rep);
            }
        }

        $stmt = $conn ->prepare("SELECT login, pwd, groupid FROM groups WHERE login = :login AND pwd = :pwd;");
        $hashPwd = hash('sha256', filter_var($pwd, FILTER_SANITIZE_STRING));
        $stmt->bindValue(':login', filter_var($login, FILTER_SANITIZE_STRING), PDO::PARAM_STR);
        $stmt->bindValue(':pwd', $hashPwd, PDO::PARAM_STR);
        $stmt->execute();
        $rep = array("id" => array());
        foreach($stmt as $element){
            if($element[0] === $login && $element[1] === $hashPwd){
                array_push($rep["id"], 'group');
                array_push($rep["id"], $element[2]);
                $connected = true;
                setcookie('connected',$connected,mktime(12,34,00,04,01,2030));
                echo json_encode($rep);
            }
        }

        if($connected === false){
            return false;
        }else
        {
            return true;
        }
    }
    catch(Exception $e){
        echo 'Exception reçue : ',  $e->getMessage(), "\n";
        return false;
    }

}

//recupere info intervenant
function getenseignant($idadmin)
{
    $conn = _getConnection();
    try{
        $stmt = $conn ->prepare("SELECT id,nom,login FROM enseignant WHERE idadmin=:idadmin;");
        $stmt->bindValue(':idadmin', filter_var($idadmin, FILTER_SANITIZE_STRING), PDO::PARAM_STR);
        $stmt->execute();

        $res = array("prof" => array());
        foreach($stmt as $element){  
            array_push($res["prof"], $element);
        }
        echo json_encode($res);
    } catch(Exception $e){
     echo 'Exception reçue : ',  $e->getMessage(), "\n";
 }
}

//recupere info salle
function getsalle($idadmin)
{
    $conn = _getConnection();
    try{
        $stmt = $conn ->prepare("SELECT id,nom FROM salle WHERE idadmin=:idadmin;");
        $stmt->bindValue(':idadmin', filter_var($idadmin, FILTER_SANITIZE_STRING), PDO::PARAM_STR);
        $stmt->execute();

        $res = array("salle" => array());
        foreach($stmt as $element){  
            array_push($res["salle"], $element);
        }
        echo json_encode($res);
    } catch(Exception $e){
     echo 'Exception reçue : ',  $e->getMessage(), "\n";
 }
}

//recupere info groupe
function getGroups($idadmin){
    $conn = _getConnection();
    try{
        $stmt = $conn ->prepare("SELECT groupid, name, login FROM groups WHERE idadmin=:idadmin;");
        $stmt->bindValue(':idadmin', filter_var($idadmin, FILTER_SANITIZE_STRING), PDO::PARAM_STR);
        $stmt->execute();

        $rep = array("groups" => array());
        foreach($stmt as $element){  
            array_push($rep["groups"], $element);
        }
        echo json_encode($rep);
    } catch(Exception $e){
     echo 'Exception reçue : ',  $e->getMessage(), "\n";
 }
}

//recupere info evenement
function getWeekByGroupId($groupid,$date,$type)
{
    if($type=='enseignant')
    {
        $conn = _getConnection();
        try{
            $stmt = $conn ->prepare("SELECT adeCase.id, adeCase.groupid, subject, date, hour, hourfin,mindebut,minutefin, type, enseignant.nom, groups.name, salle.nom FROM adeCase LEFT JOIN enseignant ON adeCase.idintervenant = enseignant.id LEFT JOIN groups ON adeCase.groupid = groups.groupid LEFT JOIN salle ON adeCase.idlieu = salle.id where adeCase.idintervenant=:groupid and date BETWEEN :date AND DATE_ADD(:date, INTERVAL 7 DAY);");
            $stmt->bindValue(':groupid', filter_var($groupid, FILTER_SANITIZE_STRING), PDO::PARAM_STR);
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
    }else{
        $conn = _getConnection();
        try{
            $stmt = $conn ->prepare("SELECT adeCase.id, adeCase.groupid, subject, date, hour, hourfin,mindebut,minutefin, type, enseignant.nom, groups.name, salle.nom FROM adeCase LEFT JOIN enseignant ON adeCase.idintervenant = enseignant.id LEFT JOIN groups ON adeCase.groupid = groups.groupid LEFT JOIN salle ON adeCase.idlieu = salle.id WHERE adeCase.groupid = :groupid and date BETWEEN :date AND DATE_ADD(:date, INTERVAL 7 DAY);");
            $stmt->bindValue(':groupid', filter_var($groupid, FILTER_SANITIZE_STRING), PDO::PARAM_STR);
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
    
}



/*-------------------------------------------------------------------*/
_closeConnection(_getConnection());
?>