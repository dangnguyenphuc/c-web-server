import { StandingLeft } from "./state.js";
import { StandingRight } from "./state.js";
import { SittingLeft } from "./state.js";
import { SittingRight } from "./state.js";
import { RunningLeft } from "./state.js";
import { RunningRight } from "./state.js";
import { JumpingLeft } from "./state.js";
import { JumpingRight } from "./state.js";
import { FallingLeft } from "./state.js";
import { FallingRight } from "./state.js";
import { GettingDownLeft } from "./state.js";
import { GettingDownRight } from "./state.js";
export default class Player{
    constructor(gameWidth,gameHeight){
        this.gameWidth = gameWidth;
        this.gameHeight = gameHeight;
        this.states = [ new StandingLeft(this), new StandingRight(this), 
                        new SittingLeft(this), new SittingRight(this),
                        new RunningLeft(this), new RunningRight(this),
                        new JumpingLeft(this), new JumpingRight(this),
                        new FallingLeft(this), new FallingRight(this),
                        new GettingDownLeft(this),new GettingDownRight(this)];
        this.currentState = this.states[1];
        this.image = document.getElementById("dogImage");
        this.width = 200;
        this.height = 181.83;
        this.x = this.gameWidth/2 - this.width/2;
        this.y = this.gameHeight - this.height;
        this.frameX = 0;
        this.frameY = 0;
        this.speed = 0;
        this.maxSpeed = 10;
        this.vy = 0
        this.weight = 1;
        this.maxFrame = 6;
        this.fps = 30;
        this.frameTimer = 0;
        this.frameInterval = 1000/this.fps;
    }
    draw(context,deltaTime){
        if(this.frameTimer  < this.frameInterval){
            if(this.frameX < this.maxFrame) this.frameX++;
            else this.frameX = 0;
            this.frameTimer = 0;
        }
        else this.frameTimer += deltaTime;
        context.drawImage(  this.image, 
                            this.width*this.frameX, this.height*this.frameY, this.width, this.height,
                            this.x, this.y, 
                            this.width, this.height );
    }
    update(input){
        this.currentState.handleInput(input);
        this.x += this.speed;
        if(this.x<=0) this.x = 0;
        if(this.x>= this.gameWidth - this.width) this.x = this.gameWidth - this.width;
        this.y += this.vy
        if(!this.onGround()){
            this.vy += this.weight;
        }
        else this.vy = 0;
        
        if(this.y > this.gameHeight - this.height)  this.y = this.gameHeight - this.height;
    }
    setState(state){
        this.currentState = this.states[state];
        this.currentState.enter();
    }
    onGround(){
        return this.y >= this.gameHeight - this.height
    }
}