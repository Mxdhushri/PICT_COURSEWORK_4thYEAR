pragma solidity ^0.8.0; //Instruction for the compiler which solidity version to use

contract Bank {
    mapping (address => uint) balances;

    function deposit() public payable{
        balances[msg.sender] = balances[msg.sender] + msg.value;
    }

    function withdraw(uint amount) public {
        require(amount <= balances[msg.sender], "Insufficient Balance");
        balances[msg.sender] = balances[msg.sender] - amount;
        payable(msg.sender).transfer(amount);
    }

    function checkBalance() public view returns (uint) {
        return balances[msg.sender];
    }
}