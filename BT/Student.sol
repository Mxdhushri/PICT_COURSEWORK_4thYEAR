pragma solidity ^0.8.0;

contract Student {

    struct Student {
        uint rollNo;
        string name;
    }

    Student[] public students;
    mapping (uint => Student) studentsMapping; 

    function addStudent(uint rollNo, string memory name) public {
        students.push(Student(rollNo, name));
        studentsMapping[rollNo] = Student(rollNo, name);
    }

    function getStudent(uint _rollNo) public view returns (uint rollNo, string memory name) {
        return (studentsMapping[_rollNo].rollNo, studentsMapping[_rollNo].name);
    }

    function getStudent2(uint _rollNo) public view returns (uint rollNo, string memory name) {
        for(uint i=0;i<students.length;i++) {
            if(students[i].rollNo == _rollNo) {
                return (students[i].rollNo, students[i].name);
            }
        }
        revert("Student not found");
    }
}